#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <getopt.h>
#include <exports.h>
#include <linux/types.h>

#define BUF_LEN (256)

#define SPI_PORT 0
#define DEFAULT_TX_TIMEOUT (5000)
#define DEFAULT_RX_TIMEOUT (20)


#define BSWAP_16(val)                        \
        (((((uint16_t)(val)) & 0x00ff) << 8) \
         | ((((uint16_t)(val)) & 0xff00) >> 8))

extern int spi_init(uint8_t port);
extern int spi_read_write(uint8_t port, void* rbuf, void* wbuf, int len,  int *count, int timeout_ms);
extern int spi_read_write(uint8_t port, void* rbuf, void* wbuf, int len,  int *count, int timeout_ms);
extern int spi_read_write(uint8_t port, void* rbuf, void* wbuf, int len,  int *count, int timeout_ms);
static uint8_t tx_buf[BUF_LEN];
static uint8_t rx_buf[BUF_LEN];

static const uint8_t packet_header[2] = {0xa5, 0x3c};

// struct {
//     uint8_t start[2];
//     uint8_t cmd[2];
//     uint8_t in_len[4];
//     uint8_t crc[4];
// } cmd_t __attribute__((packed));


enum icq530_cmd {
    BIST_START = 0x0100,
    AUTO_ADDRESSING = 0x0200,
    BIST_FIX = 0x0300,
    SOFT_RESET = 0x0400,
    BIST_COLLECT = 0x0B00,
    WRITE_JOB = 0x0700,
    READ_NONCE = 0x0800,
    WRITE_REGISTER = 0x0900,
    READ_REGISTER = 0x0A00,
    TVSENSOR_ACCESS = 0x0C00,
    READ_TV_MAX = 0x1C00,
    SEND_OPCODE = 0x0D00,
};

#define RESP_BIST_START_LEN      (3 * sizeof(uint16_t))
#define RESP_AUTO_ADDRESSING_LEN (4 * sizeof(uint16_t))
#define RESP_BIST_FIX_LEN        (0 * sizeof(uint16_t))
#define RESP_SOFT_RESET_LEN      (0 * sizeof(uint16_t))
#define RESP_BIST_COLLECT_LEN    (0 * sizeof(uint16_t))
#define RESP_WRITE_JOB_LEN       (50 * sizeof(uint16_t))
#define RESP_READ_NONCE_LEN      (3 * sizeof(uint16_t))
#define RESP_WRITE_REGISTER_LEN  (6 * sizeof(uint16_t))
#define RESP_READ_REGISTER_LEN   (6 * sizeof(uint16_t))
#define RESP_TVSENSOR_ACCESS_LEN (0 * sizeof(uint16_t))
#define RESP_READ_TV_MAX_LEN     (0 * sizeof(uint16_t))
#define RESP_SEND_OPCODE_LEN     (3 * sizeof(uint16_t))

static void __attribute__((unused)) hexdump(void *data, uint32_t len, char *name)
{
    if (!data)
        return;

    if (name)
        printf("%s:\n", name);

    for (int i = 0; i < len; i++) {
        printf("%02x ", ((uint8_t *)data)[i]);
        if (i % 16 == 15)
            printf("\n");
    }

    printf("\n");
}

static int do_parse_BIST_START(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_BIST_START_LEN;
    int xfer_len;
    printf("Enter %s\n", __func__);
    if (len < resp_len)
        return -1;

    memcpy(tx_buf, buf, resp_len);

    return spi_read_write(SPI_PORT, NULL, tx_buf, resp_len, &xfer_len, DEFAULT_TX_TIMEOUT);;
}
static int do_parse_AUTO_ADDRESSING(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_AUTO_ADDRESSING_LEN;
    int xfer_len;
    printf("Enter %s\n", __func__);
    if (len < resp_len)
        return -1;
    
    memcpy(tx_buf, buf, resp_len);
    tx_buf[5] = 1;

    return spi_read_write(SPI_PORT, NULL, tx_buf, resp_len, &xfer_len, DEFAULT_TX_TIMEOUT);;
}
static int do_parse_BIST_FIX(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_BIST_FIX_LEN;
    printf("Enter %s\n", __func__);
    if (len < resp_len)
        return -1;

    return 0;
}
static int do_parse_SOFT_RESET(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_SOFT_RESET_LEN;
    printf("Enter %s\n", __func__);
    if (len < resp_len)
        return -1;

    return 0;
}
static int do_parse_BIST_COLLECT(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_BIST_COLLECT_LEN;
    printf("Enter %s\n", __func__);
    if (len < resp_len)
        return -1;

    return 0;
}
static int do_parse_WRITE_JOB(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_WRITE_JOB_LEN;
    printf("Enter %s\n", __func__);

    uint16_t crc16;
    int xfer_len;

    if (len < resp_len)
        return -1;

    // TODO: check crc
    (void)crc16;
    
    memcpy(tx_buf, buf, resp_len);


    uint32_t payload[19];
    uint64_t difficult;
    uint32_t e_nonce;
    uint32_t extradifficult;

    memcpy(payload, (uint32_t *)(buf + 4), 76);
    memcpy(&difficult, (uint32_t *)(buf + 80), 8);
    memcpy(&e_nonce, (uint32_t *)(buf + 88), 4);
    memcpy(&extradifficult, (uint32_t *)(buf + 92), 4);

    hexdump((uint8_t *)payload, sizeof(payload), "Blob");
    printf("difficult=%016llx\n", difficult);
    printf("e_nonce=%08x\n", e_nonce);
    printf("extradifficult=%08x\n", extradifficult);

    return spi_read_write(SPI_PORT, NULL, tx_buf, resp_len, &xfer_len, DEFAULT_TX_TIMEOUT);;
}
static int do_parse_READ_NONCE(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_READ_NONCE_LEN;
    int xfer_len;

    // printf("Enter %s\n", __func__);
    if (len < resp_len)
        return -1;

    memcpy(tx_buf, buf, resp_len);

    return spi_read_write(SPI_PORT, NULL, tx_buf, resp_len, &xfer_len, DEFAULT_TX_TIMEOUT);;
}
static int do_parse_WRITE_REGISTER(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_WRITE_REGISTER_LEN;
    printf("Enter %s\n", __func__);

    uint16_t crc16 = 0x1234;
    int xfer_len;
    if (len < resp_len)
        return -1;

    (void)crc16;

    memcpy(tx_buf, buf, resp_len);
    return spi_read_write(SPI_PORT, NULL, tx_buf, resp_len, &xfer_len, DEFAULT_TX_TIMEOUT);;
}
static int do_parse_READ_REGISTER(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_READ_REGISTER_LEN;
    printf("Enter %s\n", __func__);
    uint16_t rddata = 0x5678;

    uint16_t crc16 = 0x1234;
    int xfer_len;
    if (len < resp_len)
        return -1;

    (void)crc16;

    memcpy(tx_buf, buf, 6);
    tx_buf[3] = 0x1;
    *(uint16_t *)&tx_buf[6] = rddata;
    *(uint16_t *)&tx_buf[8] = crc16;
    *(uint16_t *)&tx_buf[10] = 0x0;

    return spi_read_write(SPI_PORT, NULL, tx_buf, resp_len, &xfer_len, DEFAULT_TX_TIMEOUT);;
}
static int do_parse_TVSENSOR_ACCESS(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_TVSENSOR_ACCESS_LEN;
    printf("Enter %s\n", __func__);
    if (len < resp_len)
        return -1;

    return 0;
}
static int do_parse_READ_TV_MAX(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_READ_TV_MAX_LEN;
    printf("Enter %s\n", __func__);
    if (len < resp_len)
        return -1;

    return 0;
}
static int do_parse_SEND_OPCODE(const uint8_t *buf, uint32_t len)
{
    int resp_len = RESP_SEND_OPCODE_LEN;
    int xfer_len;
    printf("Enter %s\n", __func__);
    if (len < resp_len)
        return -1;
    
    memcpy(tx_buf, buf, 4);
    memset(&tx_buf[3], 0, 2);

    return spi_read_write(SPI_PORT, NULL, tx_buf, resp_len, &xfer_len, DEFAULT_TX_TIMEOUT);;
}

static int parse_rx(uint8_t *buf, uint32_t len)
{
    int packet_len, left_len = -1;
    uint8_t *pa = NULL, *pb = NULL;
    uint16_t cmd = 0;
    int rc = 0;

    packet_len = sizeof(packet_header);
    for (int i = 0; i < BUF_LEN - packet_len; i++) {
        if (!memcmp(&buf[i], packet_header, packet_len)) {
            pa = pb = &buf[i];
            left_len = BUF_LEN - i;
            break;
        }
    }

    if (!pb || left_len < 0) {
        /* Can not find  packet_header */
        return -1;
    }
    pb += 2;

    cmd = *(uint16_t *)pb;
    pb += 2;

    // TODO: READ_TV_MAX
    switch (BSWAP_16(cmd) & (0xFU << 8)) {
    case BIST_START:
        rc = do_parse_BIST_START(pa, left_len);
        break;
    case AUTO_ADDRESSING:
        rc = do_parse_AUTO_ADDRESSING(pa, left_len);
        break;
    case BIST_FIX:
        rc = do_parse_BIST_FIX(pa, left_len);
        break;
    case SOFT_RESET:
        rc = do_parse_SOFT_RESET(pa, left_len);
        break;
    case BIST_COLLECT:
        rc = do_parse_BIST_COLLECT(pa, left_len);
        break;
    case WRITE_JOB:
        rc = do_parse_WRITE_JOB(pa, left_len);
        break;
    case READ_NONCE:
        rc = do_parse_READ_NONCE(pa, left_len);
        break;
    case WRITE_REGISTER:
        rc = do_parse_WRITE_REGISTER(pa, left_len);
        break;
    case READ_REGISTER:
        rc = do_parse_READ_REGISTER(pa, left_len);
        break;
    case TVSENSOR_ACCESS:
        rc = do_parse_TVSENSOR_ACCESS(pa, left_len);
        break;
    case READ_TV_MAX:
        rc = do_parse_READ_TV_MAX(pa, left_len);
        break;
    case SEND_OPCODE:
        rc = do_parse_SEND_OPCODE(pa, left_len);
        break;
    default:
        printf("Invaid cmd\n");
        break;
    }

    return rc;
}

static int rxa_spi_main(int argc, char *argv[])
{
    spi_init(SPI_PORT);
    int xfer_len;

    // for (int i = 0; i < sizeof(tx_buf); i++)
    //     tx_buf[i] = i & 0xff;
    // while (1) {
    //     spi_read_write(SPI_PORT, NULL, tx_buf, 129, &xfer_len, DEFAULT_TX_TIMEOUT);
    // }
    
    while (1) {
        spi_read_write(SPI_PORT, rx_buf, NULL, BUF_LEN, &xfer_len, DEFAULT_RX_TIMEOUT);
        if (xfer_len) {
            // for (int i = 0; i < xfer_len; i++) {
            //     printf("%02x ", rx_buf[i]);
            //     if (i % 16 == 15)
            //         printf("\n");
            // }
            // printf("\n");
        //    spi_read_write(SPI_PORT, NULL, rx_buf, xfer_len, &xfer_len, DEFAULT_TX_TIMEOUT);
            parse_rx(rx_buf, xfer_len);
        }
        

        // udelay(10*1000);
    }
    return 0;
}

static void rxa_spi_init(void) { register_testbench("rxa_spi", rxa_spi_main, NULL); }

testbench_init(rxa_spi_init);
