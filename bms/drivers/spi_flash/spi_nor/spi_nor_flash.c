#include <malloc.h>
#include <common.h>
#include <spi.h>
#include <spi-common.h>
#include "spi_nor_flash.h"

#define DUMMY_BYTE 0x00

#define SPI_FLASH_PAGE_SIZE   (256)
#define SPI_FLASH_SECTOR_SIZE (16 * SPI_FLASH_PAGE_SIZE)
#define SPI_FLASH_BLOCK_SIZE  (16 * SPI_FLASH_SECTOR_SIZE)
#define SPI_FLASH_FULL_SIZE   (512 * SPI_FLASH_BLOCK_SIZE)

#define SPI_FLASH_DummyDataByte    0x00
#define SPI_FLASH_WriteEnable      0x06
#define SPI_FLASH_WriteDisable     0x04
#define SPI_FLASH_ReadStatusReg    0x05
#define SPI_FLASH_WriteStatusReg   0x01
#define SPI_FLASH_ReadData         0x03
#define SPI_FLASH_FastReadData     0x0B
#define SPI_FLASH_FastReadDual     0x3B
#define SPI_FLASH_PageProgram      0x02
#define SPI_FLASH_BlockErase       0xD8
#define SPI_FLASH_SectorErase      0x20
#define SPI_FLASH_ChipErase        0xC7
#define SPI_FLASH_PowerDown        0xB9
#define SPI_FLASH_ReleasePowerDown 0xAB
#define SPI_FLASH_DeviceID         0xAB
#define SPI_FLASH_ManufactDeviceID 0x90
#define SPI_FLASH_JedecDeviceID    0x9F
#define SPI_FLASH_ENABLE_POR       0x66
#define SPI_FLASH_POR              0x99
#define SPI_FLASH_LOCK             0x7E
#define SPI_FLASH_UNLOCK           0x98

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
  uint8_t buf[4] = {0};
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]    = SPI_FLASH_JedecDeviceID;
  trans.cmd_size  = 1;
  trans.rx_data   = buf;
  trans.data_size = 4;

  single_transfer(handler, &trans);

  printf("Manufacturer ID = 0x%x\n", buf[0]);
  printf("Device ID = 0x%x%x%x\n", buf[1], buf[2], buf[3]);
  return 0;
}

static void wait_busy(SPI_HandleTypeDef *handler) {
  uint8_t sr = 0;
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]    = SPI_FLASH_ReadStatusReg;
  trans.cmd_size  = 1;
  trans.rx_data   = &sr;
  trans.data_size = 1;
  do {
    single_transfer(handler, &trans);
    udelay(10);
  } while (sr & 0x01);
}

static void write_page(SPI_HandleTypeDef *handler, uint8_t *pBuffer,
                       uint32_t addr, uint32_t byte_num) {
  // Sending Write Enable.
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]   = SPI_FLASH_WriteEnable;
  trans.cmd_size = 1;
  single_transfer(handler, &trans);

  // Sending Write command & address.
  trans.cmd[0]    = SPI_FLASH_PageProgram;
  trans.cmd[1]    = (uint8_t)(addr >> 16);
  trans.cmd[2]    = (uint8_t)(addr >> 8);
  trans.cmd[3]    = (uint8_t)(addr);
  trans.cmd_size  = 4;
  trans.tx_data   = pBuffer;
  trans.data_size = byte_num;
  single_transfer(handler, &trans);

  // Waiting for write done.
  wait_busy(handler);
}

static void write_noCheck(SPI_HandleTypeDef *handler, uint8_t *pBuffer,
                          uint32_t addr, uint32_t byte_num) {
  uint32_t pageremain;
  pageremain =
      SPI_FLASH_PAGE_SIZE - addr % SPI_FLASH_PAGE_SIZE; //单页剩余的字节数
  if (byte_num <= pageremain) { //不大于SPI_FLASH_PAGE_SIZE个字节
    pageremain = byte_num;
  }
  while (1) {
    write_page(handler, pBuffer, addr, pageremain);
    if (byte_num == pageremain) { //写入结束了
      break;
    } else {
      pBuffer += pageremain;
      addr += pageremain;

      byte_num -= pageremain; //减去已经写入了的字节数
      if (byte_num >
          SPI_FLASH_PAGE_SIZE) { //一次可以写入SPI_FLASH_PAGE_SIZE个字节
        pageremain = SPI_FLASH_PAGE_SIZE;
      } else {
        pageremain = byte_num; //不够256个字节了
      }
    }
  }
}

static void nor_reset(SPI_HandleTypeDef *handler) {
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]   = SPI_FLASH_ENABLE_POR;
  trans.cmd_size = 1;
  single_transfer(handler, &trans);

  udelay(100);

  trans.cmd[0] = SPI_FLASH_POR;
  single_transfer(handler, &trans);

  udelay(1000);
}

static SPI_HandleTypeDef *nor_init(SPI_InitTypeDef *init) {
  SPI_HandleTypeDef *spi_handler;
  /*
   SPI_InitTypeDef spi_init;
   if(init->mode & 0x01)
       spi_init.CLKPhase =  SPI_PHASE_2EDGE;
   else
       spi_init.CLKPhase =  SPI_PHASE_1EDGE;

   if(init->mode & 0x02)
       spi_init.CLKPolarity =  SPI_POLARITY_HIGH;
   else
       spi_init.CLKPolarity =  SPI_POLARITY_LOW;

   spi_init.cs_mode = init->cs_mode;
   spi_init.cs_pin = init->cs_pin;
   spi_init.dataSize = init->dataSize;
   spi_init.freq_hz = init->freq_hz
   spi_init.mode = SPI_MODE_MASTER;
   */
  spi_handler = itcs_spi_init(init);
  if (spi_handler == NULL) {
    return NULL;
  }

  nor_reset(spi_handler);
  get_id(spi_handler);

  return spi_handler;
}

static uint32_t nor_read(SPI_HandleTypeDef *handler, uint8_t *pBuffer,
                         uint32_t addr, uint32_t byte_num) {

  // Sending read command & address.
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd[0]    = SPI_FLASH_ReadData;
  trans.cmd[1]    = (uint8_t)(addr >> 16);
  trans.cmd[2]    = (uint8_t)(addr >> 8);
  trans.cmd[3]    = (uint8_t)(addr);
  trans.cmd_size  = 4;
  trans.rx_data   = pBuffer;
  trans.data_size = byte_num;
  single_transfer(handler, &trans);

  // Waiting for operation done.
  wait_busy(handler);

  return byte_num;
}

static bool nor_erase(SPI_HandleTypeDef *handler, SPI_FLASH_ERASE_TYPE type,
                      uint32_t addr) {

  if (type == SPI_FLASH_ERASE_FULL_CHIP) {

    // Waiting for last operation done.
    wait_busy(handler);

    // Sending Write Enable.
    memset(&trans, 0, sizeof(struct spi_transfer));
    trans.cmd[0]   = SPI_FLASH_WriteEnable;
    trans.cmd_size = 1;
    single_transfer(handler, &trans);
    udelay(10);

    memset(&trans, 0, sizeof(struct spi_transfer));
    trans.cmd[0]   = SPI_FLASH_ChipErase;
    trans.cmd_size = 1;
    single_transfer(handler, &trans);

    // Waiting for erasing done.
    wait_busy(handler);

  } else if (type == SPI_FLASH_ERASE_SECTOR) {
    if (SPI_FLASH_SECTOR_SIZE == 0) {
      printf("spi flash csector erase format does not support.\n");
      return false;
    }
    DEBUG_SPI_LOG("spi nor flash erase sector.\n");
    // nor flash needed
    addr *= SPI_FLASH_SECTOR_SIZE;
    // Waiting for last operation done.
    wait_busy(handler);

    // Sending Write Enable.
    memset(&trans, 0, sizeof(struct spi_transfer));
    trans.cmd[0]   = SPI_FLASH_WriteEnable;
    trans.cmd_size = 1;
    single_transfer(handler, &trans);
    udelay(10);

    memset(&trans, 0, sizeof(struct spi_transfer));
    trans.cmd[0]   = SPI_FLASH_SectorErase;
    trans.cmd[1]   = (uint8_t)(addr >> 16);
    trans.cmd[2]   = (uint8_t)(addr >> 8);
    trans.cmd[3]   = (uint8_t)(addr);
    trans.cmd_size = 4;
    single_transfer(handler, &trans);
    udelay(10);

    // Waiting for erasing done.
    wait_busy(handler);

  } else if (type == SPI_FLASH_ERASE_BLOCK) {
    printf("block erase is not support in gd25lx256e.\n");
  } else {
    printf("erase way is not support in gd25lx256e.\n");
    return false;
  }
  return true;
}

static uint32_t nor_write(SPI_HandleTypeDef *handler, uint8_t *pBuffer,
                          uint32_t addr, uint32_t byte_num) {

  uint32_t secpos;
  uint16_t secoff;
  uint16_t secremain;
  uint16_t i;
  uint8_t *flash_buf = (uint8_t *)malloc(SPI_FLASH_SECTOR_SIZE);
  secpos             = addr / SPI_FLASH_SECTOR_SIZE; //扇区地址
  secoff             = addr % SPI_FLASH_SECTOR_SIZE; //在扇区内的偏移
  secremain = SPI_FLASH_SECTOR_SIZE - secoff;        //扇区剩余空间大小
  if (byte_num <= secremain) { //不大于SPI_FLASH_SECTOR_SIZE个字节
    secremain = byte_num;
  }
  while (1) {
    nor_read(handler, flash_buf, secpos * SPI_FLASH_SECTOR_SIZE,
             SPI_FLASH_SECTOR_SIZE);       //读出整个扇区的内容
    for (i = 0; i < secremain; i++) {      //校验数据
      if (flash_buf[secoff + i] != 0xFF) { //需要擦除
        break;
      }
    }
    if (i < secremain) {                                  //需要擦除
      nor_erase(handler, SPI_FLASH_ERASE_SECTOR, secpos); //擦除这个扇区
      for (i = 0; i < secremain; i++) {                   //复制
        flash_buf[i + secoff] = pBuffer[i];
      }
      write_noCheck(handler, flash_buf, secpos * SPI_FLASH_SECTOR_SIZE,
                    SPI_FLASH_SECTOR_SIZE); //写入整个扇区
    } else {
      write_noCheck(handler, pBuffer, addr,
                    secremain); //写已经擦除了的,直接写入扇区剩余区间.
    }

    if (byte_num == secremain) { //写入结束了
      break;
    } else {                                  //写入未结束
      secpos++;                               //扇区地址增1
      secoff = 0;                             //偏移位置为0
      pBuffer += secremain;                   //指针偏移
      addr += secremain;                      //写地址偏移
      byte_num -= secremain;                  //字节数递减
      if (byte_num > SPI_FLASH_SECTOR_SIZE) { //下一个扇区还是写不完
        secremain = SPI_FLASH_SECTOR_SIZE;
      } else { //下一个扇区可以写完了
        secremain = byte_num;
      }
    }
  }

  free(flash_buf);
  return byte_num;
}

static uint32_t nor_get_alignment(SPI_HandleTypeDef *handler) {
  return SPI_FLASH_PAGE_SIZE;
}

static bool nor_write_protect(SPI_HandleTypeDef *handler, bool enable) {
  /*
  memset(&trans, 0, sizeof(struct spi_transfer));
  trans.cmd_size = 1;

  if (enable) {
    trans.cmd[0] = SPI_FLASH_LOCK;
  } else {
    trans.cmd[0] = SPI_FLASH_UNLOCK;
  }

  single_transfer(handler, &trans);
  */
  return true;
}

struct spi_flash_operations f_ops_spi_nor = {.init          = nor_init,
                                             .read          = nor_read,
                                             .write         = nor_write,
                                             .erase         = nor_erase,
                                             .get_alignment = nor_get_alignment,
                                             .write_protect = nor_write_protect,
                                             .reset         = nor_reset};