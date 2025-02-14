#include <malloc.h>
#include <common.h>
#include <spi.h>
#include <spi-common.h>
#include "spi_nand_flash.h"

#define DUMMY_BYTE 0x00

#define SPI_FLASH_PAGE_SIZE          (2 * 1024)
#define SPI_FLASH_PAGE_NUM_PER_BLOCK (64)
#define SPI_FLASH_SECTOR_SIZE        (0)
#define SPI_FLASH_BLOCK_SIZE                                                   \
  (SPI_FLASH_PAGE_NUM_PER_BLOCK * SPI_FLASH_PAGE_SIZE)
#define SPI_FLASH_BLOCK_NUM (1024)
#define SPI_FLASH_FULL_SIZE (SPI_FLASH_BLOCK_NUM * SPI_FLASH_BLOCK_SIZE)

#define SPI_FLASH_WRITE_ENABLE         0x06
#define SPI_FLASH_WRITE_DISABLE        0x04
#define SPI_FLASH_GET_FEATURE          0x0f
#define SPI_FLASH_SET_FEATURE          0x1f
#define SPI_FLASH_PAGE_READ            0x13
#define SPI_FLASH_READ_CACHE           0x03
#define SPI_FLASH_FAST_READ_CACHE      0x0b
#define SPI_FLASH_READ_CACHE_X2        0x3b
#define SPI_FLASH_READ_CACHE_X4        0x6b
#define SPI_FLASH_READ_CACHE_DUAL_IO   0xbb
#define SPI_FLASH_READ_CACHE_QUAD_IO   0xeb
#define SPI_FLASH_READ_ID              0x9f
#define SPI_FLASH_PROGRAM_LOAD         0x02
#define SPI_FLASH_PROGRAM_LOAD4        0x32
#define SPI_FLASH_PROGRAM_EXEC         0x10
#define SPI_FLASH_PROGRAM_LOAD_RANDOM  0x84
#define SPI_FLASH_PROGRAM_LOAD_RANDOM4 0xc4
#define SPI_FLASH_BLOCK_ERASE          0xd8
#define SPI_FLASH_RESET                0xff
#define SPI_FLASH_ENABLE_POR           0x66
#define SPI_FLASH_POR                  0x99
#define SPI_FLASH_JedecDeviceID        0x9F

static struct spi_transfer trans;

static int single_transfer(SPI_HandleTypeDef *handler,
                           struct spi_transfer *trans) {
  int ret              = 0;
  uint32_t tx_data_len = trans->cmd_size + trans->data_size;

  uint32_t data_bytes_start_idx = trans->cmd_size;
  uint8_t *tx_data              = (uint8_t *)malloc(tx_data_len);
  uint8_t *rx_data              = (uint8_t *)malloc(tx_data_len);
  DEBUG_SPI_LOG("spi single transfer whole len = %d, cmd = 0x%x\n", tx_data_len,
                trans->cmd[0]);

  if (trans->cmd_size > 0) {
    memcpy(tx_data, trans->cmd, trans->cmd_size);
  }

  if (trans->rx_data != NULL) {
    if (trans->data_size > 0) {
      memset(&tx_data[data_bytes_start_idx], DUMMY_BYTE, trans->data_size);
    } else {
      printf("tx data buffer not null but data size is zero.\n");
      free(tx_data);
      free(rx_data);
      return -1;
    }
    // itcs_spi_chip_select(handler, 0);
    ret =
        itcs_spi_transmit_receive(handler, tx_data, rx_data, tx_data_len, true);
    // itcs_spi_chip_select(handler, 1);
    memcpy(trans->rx_data, &rx_data[data_bytes_start_idx], trans->data_size);
    free(tx_data);
    free(rx_data);
    return ret;
  }

  if ((trans->tx_data != NULL) && (trans->data_size > 0)) {
    memcpy(&tx_data[data_bytes_start_idx], trans->tx_data, trans->data_size);
  }

  // itcs_spi_chip_select(handler, 0);
  ret = itcs_spi_transmit(handler, tx_data, tx_data_len, true);
  // itcs_spi_chip_select(handler, 1);
  free(tx_data);
  free(rx_data);
  return ret;
}

static int get_id(SPI_HandleTypeDef *handler) {
  uint8_t buf[2] = {0};
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]    = SPI_FLASH_JedecDeviceID;
  trans.cmd[1]    = DUMMY_BYTE;
  trans.cmd_size  = 2;
  trans.rx_data   = buf;
  trans.data_size = 2;

  single_transfer(handler, &trans);

  printf("Manufacturer ID = 0x%x\n", buf[0]);
  printf("Device ID = 0x%x\n", buf[1]);

  return 0;
}

static void nand_reset(SPI_HandleTypeDef *handler) {
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]   = SPI_FLASH_RESET;
  trans.cmd_size = 1;

  single_transfer(handler, &trans);
  udelay(1000);

  trans.cmd[0] = SPI_FLASH_ENABLE_POR;
  single_transfer(handler, &trans);
  udelay(100);

  trans.cmd[0] = SPI_FLASH_POR;
  single_transfer(handler, &trans);

  udelay(1000);
}

static void wait_busy(SPI_HandleTypeDef *handler) {
  uint8_t sr = 0;
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]    = SPI_FLASH_GET_FEATURE;
  trans.cmd[1]    = 0xC0;
  trans.cmd_size  = 2;
  trans.rx_data   = &sr;
  trans.data_size = 1;

  do {
    single_transfer(handler, &trans);
    udelay(10);
  } while (sr & 0x01);
}

static int parse_addr(uint32_t addr, uint32_t *block_addr, uint32_t *page_addr,
                      uint32_t *page_offset, uint32_t *colum_addr,
                      uint32_t *row_addr) {
  uint32_t ba, pa, po, ca, ra;

  if (addr > SPI_FLASH_FULL_SIZE) {
    printf("spi nand flash address out of range!\n");
    return -1;
  }

  ba = addr / (uint32_t)SPI_FLASH_BLOCK_SIZE;

  pa = (addr - (ba * (uint32_t)SPI_FLASH_BLOCK_SIZE)) /
       (uint32_t)SPI_FLASH_PAGE_SIZE;

  po = addr - (ba * (uint32_t)SPI_FLASH_BLOCK_SIZE) -
       (pa * (uint32_t)SPI_FLASH_PAGE_SIZE);

  ca = po;
  ra = (pa & 0x3F) | ((ba & 0x3FF) << 6);

  DEBUG_SPI_LOG("---------------------------\n");
  DEBUG_SPI_LOG("spi address parse:\n");
  DEBUG_SPI_LOG("user    address: 0x%x\n", addr);
  if (block_addr) {
    *block_addr = ba;
    DEBUG_SPI_LOG("block   address: 0x%x\n", *block_addr);
  }
  if (page_addr) {
    *page_addr = pa;
    DEBUG_SPI_LOG("page    address: 0x%x\n", *page_addr);
  }
  if (page_offset) {
    *page_offset = po;
    DEBUG_SPI_LOG("pageoff address: 0x%x\n", *page_offset);
  }
  if (colum_addr) {
    *colum_addr = ca;
    DEBUG_SPI_LOG("column  address: 0x%x\n", *colum_addr);
  }
  if (row_addr) {
    *row_addr = ra;
    DEBUG_SPI_LOG("row     address: 0x%x\n", *row_addr);
  }
  DEBUG_SPI_LOG("---------------------------\n");
  return 0;
}

static void enable_ecc(SPI_HandleTypeDef *handler, bool enable) {

  uint8_t sr;
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]    = SPI_FLASH_GET_FEATURE;
  trans.cmd[1]    = 0xB0;
  trans.cmd_size  = 2;
  trans.rx_data   = &sr;
  trans.data_size = 1;

  single_transfer(handler, &trans);
  udelay(10);
  printf("feature 0xb0= %x\n", sr);

  trans.cmd[0] = SPI_FLASH_SET_FEATURE;
  if (enable)
    sr |= 0x10;
  else
    sr &= 0xef;
  trans.tx_data = &sr;
  trans.rx_data = NULL;

  single_transfer(handler, &trans);
  udelay(10);
}

static int read_data_in_page(SPI_HandleTypeDef *handler, uint32_t row_addr,
                             uint32_t page_offset, uint8_t *rx_ptr,
                             uint32_t size) {

  // Sending read to cache command & address.
  // this address is row address page_addr:[5:0], block_addr[15:6]
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]   = SPI_FLASH_PAGE_READ;
  trans.cmd[1]   = (uint8_t)((row_addr & 0xff0000) >> 16);
  trans.cmd[2]   = (uint8_t)((row_addr & 0xff00) >> 8);
  trans.cmd[3]   = (uint8_t)(row_addr & 0xff);
  trans.cmd_size = 4;
  single_transfer(handler, &trans);

  udelay(100);

  // Waiting for operation done.
  wait_busy(handler);

  // Read correct data from spi nand cache
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]    = SPI_FLASH_READ_CACHE;
  trans.cmd[1]    = (uint8_t)((page_offset & 0x0f00) >> 8);
  trans.cmd[2]    = (uint8_t)(page_offset & 0xff);
  trans.cmd[3]    = DUMMY_BYTE;
  trans.cmd_size  = 4;
  trans.rx_data   = rx_ptr;
  trans.data_size = size;
  single_transfer(handler, &trans);

  wait_busy(handler);

  return 0;
}

static int generate_next_page_row_addr(uint32_t row_addr,
                                       uint32_t *next_row_addr) {
  uint32_t page_addr  = row_addr & 0x3f;
  uint32_t block_addr = (row_addr >> 6) & 0x3ff;
  if (page_addr < SPI_FLASH_PAGE_NUM_PER_BLOCK) {
    page_addr++;
  } else {
    if (block_addr < SPI_FLASH_BLOCK_NUM) {
      page_addr = 0;
      block_addr++;

    } else {
      printf("address out of range.\n");
      return -1;
    }
  }
  *next_row_addr = ((block_addr & 0x3ff) << 6) | (page_addr & 0x3f);
  return 0;
}

static uint32_t write_whole_page(SPI_HandleTypeDef *handler, uint32_t block_idx,
                                 uint32_t page_idx, uint8_t *pBuffer) {
  uint32_t row_addr;
  row_addr = ((block_idx & 0x3ff) << 6) + (page_idx & 0x3f);
  DEBUG_SPI_LOG("row addr = 0x%x\n", row_addr);

  // Sending program load command
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]    = SPI_FLASH_PROGRAM_LOAD;
  trans.cmd[1]    = 0;
  trans.cmd[2]    = 0;
  trans.cmd_size  = 3;
  trans.tx_data   = pBuffer;
  trans.data_size = SPI_FLASH_PAGE_SIZE;
  single_transfer(handler, &trans);

  // Sending Write Enable.
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]   = SPI_FLASH_WRITE_ENABLE;
  trans.cmd_size = 1;
  single_transfer(handler, &trans);

  // Program execute
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]   = SPI_FLASH_PROGRAM_EXEC;
  trans.cmd[1]   = (uint8_t)((row_addr & 0xff0000) >> 16);
  trans.cmd[2]   = (uint8_t)((row_addr & 0xff00) >> 8);
  trans.cmd[3]   = (uint8_t)((row_addr & 0xff));
  trans.cmd_size = 4;
  single_transfer(handler, &trans);

  wait_busy(handler);
  return 0;
}

static uint32_t write_whole_block(SPI_HandleTypeDef *handler,
                                  uint32_t block_idx, uint8_t *pBuffer) {
  for (int i = 0; i < SPI_FLASH_PAGE_NUM_PER_BLOCK; i++) {
    write_whole_page(handler, block_idx, i,
                     &pBuffer[i * SPI_FLASH_PAGE_NUM_PER_BLOCK]);
  }
  return 0;
}

static SPI_HandleTypeDef *nand_init(SPI_InitTypeDef *init) {
  SPI_HandleTypeDef *spi_handler;

  spi_handler = itcs_spi_init(init);
  if (spi_handler == NULL) {
    return NULL;
  }

  nand_reset(spi_handler);
  get_id(spi_handler);
  enable_ecc(spi_handler, true);

  return spi_handler;
}

static uint32_t nand_read(SPI_HandleTypeDef *handler, uint8_t *pBuffer,
                          uint32_t addr, uint32_t byte_num) {

  int ret;
  uint32_t block_addr, page_addr, page_offset, colum_addr, row_addr;
  uint32_t page_head_bytes, page_mid_num, page_tail_bytes, page_remain;

  ret = parse_addr(addr, &block_addr, &page_addr, &page_offset, &colum_addr,
                   &row_addr);
  if (ret) {
    printf("spi nand read failed!\n");
    return 0;
  }

  page_remain = SPI_FLASH_PAGE_SIZE - page_offset;

  if (byte_num > page_remain) {
    page_head_bytes = page_remain;
    page_mid_num = (byte_num - page_remain) / (uint32_t)(SPI_FLASH_PAGE_SIZE);
    page_tail_bytes = (byte_num - page_remain - page_mid_num) %
                      (uint32_t)(SPI_FLASH_PAGE_SIZE);
  } else {
    page_head_bytes = byte_num;
    page_mid_num    = 0;
    page_tail_bytes = 0;
  }

  DEBUG_SPI_LOG("spi first page read bytes=%d, mid page nums=%d, last page "
                "read bytes=%d\n",
                page_head_bytes, page_mid_num, page_tail_bytes);

  read_data_in_page(handler, row_addr, page_offset, pBuffer, page_head_bytes);
  generate_next_page_row_addr(row_addr, &row_addr);

  while (page_mid_num--) {
    read_data_in_page(handler, row_addr, 0, pBuffer, SPI_FLASH_PAGE_SIZE);
    generate_next_page_row_addr(row_addr, &row_addr);
  }
  if (page_tail_bytes) {
    read_data_in_page(handler, row_addr, 0, pBuffer, page_tail_bytes);
  }

  return byte_num;
}

static bool nand_erase(SPI_HandleTypeDef *handler, SPI_FLASH_ERASE_TYPE type,
                       uint32_t addr) {
  if (type == SPI_FLASH_ERASE_FULL_CHIP) {
    printf("full chip erase is not support in gd5f1g\n");
    return false;
  } else if (type == SPI_FLASH_ERASE_SECTOR) {
    printf("sector erase is not support in gd5f1g\n");
    return false;
  } else if (type == SPI_FLASH_ERASE_BLOCK) {
    uint32_t row_addr = 0;
    parse_addr(addr, NULL, NULL, NULL, NULL, &row_addr);
    DEBUG_SPI_LOG("gd5f1g flash erase. row_addr = 0x%x\n", row_addr);
    wait_busy(handler);

    // Sending Write Enable.
    memset(&trans, 0, sizeof(struct spi_transfer));
    trans.cmd[0]   = SPI_FLASH_WRITE_ENABLE;
    trans.cmd_size = 1;
    single_transfer(handler, &trans);

    udelay(10);

    // Block erase
    memset(&trans, 0, sizeof(struct spi_transfer));
    trans.cmd[0]   = SPI_FLASH_BLOCK_ERASE;
    trans.cmd[1]   = (uint8_t)((row_addr & 0xff0000) >> 16);
    trans.cmd[2]   = (uint8_t)((row_addr & 0xff00) >> 8);
    trans.cmd[3]   = (uint8_t)(row_addr & 0xff);
    trans.cmd_size = 4;
    single_transfer(handler, &trans);

    udelay(10);

      // Reend Write Enable.
    //winbond nand flash write enable will be reset after erase or write 
    memset(&trans, 0, sizeof(struct spi_transfer));
    trans.cmd[0]   = SPI_FLASH_WRITE_ENABLE;
    trans.cmd_size = 1;
    single_transfer(handler, &trans);

    wait_busy(handler);

  } else {
    printf("erase way is not support in gd5f1g\n");
    return false;
  }
  return true;
}

static uint32_t nand_write(SPI_HandleTypeDef *handler, uint8_t *pBuffer,
                           uint32_t addr, uint32_t byte_num) {
  int ret;
  uint8_t *flash_buf = (uint8_t *)malloc(SPI_FLASH_BLOCK_SIZE);
  uint32_t block_idx, page_idx, page_offset, colum_addr, row_addr;
  uint32_t cur_blk_remain_max_bytes;
  uint32_t block_start, block_start_addr;
  uint32_t bytes_to_write = byte_num;
  //计算有多少个块需要擦除
  //找到当前块
  ret = parse_addr(addr, &block_idx, &page_idx, &page_offset, &colum_addr,
                   &row_addr);
  if (ret) {
    printf("spi nand write failed!\n");
    free(flash_buf);
    return 0;
  }

  block_start      = block_idx;
  block_start_addr = (block_start & 0x3ff) << 6;
  cur_blk_remain_max_bytes =
      (SPI_FLASH_PAGE_SIZE - page_offset) +
      ((SPI_FLASH_PAGE_NUM_PER_BLOCK - page_idx) * SPI_FLASH_PAGE_SIZE);

  uint32_t write_bytes;
  do {
    write_bytes = cur_blk_remain_max_bytes < bytes_to_write
                      ? cur_blk_remain_max_bytes
                      : bytes_to_write;
    nand_read(handler, flash_buf, block_start_addr, SPI_FLASH_BLOCK_SIZE);
    nand_erase(handler, SPI_FLASH_ERASE_BLOCK, block_start_addr);
    memcpy(&flash_buf[(page_idx * SPI_FLASH_PAGE_SIZE) + page_offset], pBuffer,
           write_bytes);
    write_whole_block(handler, block_start, flash_buf);
    cur_blk_remain_max_bytes = SPI_FLASH_BLOCK_SIZE;
    bytes_to_write -= write_bytes;
    page_offset = 0;
    page_idx    = 0;
    block_start++;
    block_start_addr += (0x1 << 6);
  } while (bytes_to_write);

  free(flash_buf);
  return byte_num;
}

static uint32_t nand_get_alignment(SPI_HandleTypeDef *handler) {
  return SPI_FLASH_BLOCK_SIZE;
}

static bool nand_write_protect(SPI_HandleTypeDef *handler, bool enable) {
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]   = SPI_FLASH_SET_FEATURE;
  trans.cmd[1]   = 0xA0;
  trans.cmd_size = 3;

  if (enable) {
    trans.cmd[2] = 0x38;
  } else {
    trans.cmd[2] = 0x00;
  }

  single_transfer(handler, &trans);

  return true;
}

struct spi_flash_operations f_ops_spi_nand = {
    .init          = nand_init,
    .read          = nand_read,
    .write         = nand_write,
    .erase         = nand_erase,
    .get_alignment = nand_get_alignment,
    .write_protect = nand_write_protect,
    .reset         = nand_reset};