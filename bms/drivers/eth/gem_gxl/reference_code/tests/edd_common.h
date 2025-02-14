/**********************************************************************
 * Copyright (C) 2018-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************/
#ifndef INCLUDE_EDD_COMMON_H
#define INCLUDE_EDD_COMMON_H

#include "edd_log.h"
#include "cedi_priv.h"
#include "emac_registers.h"

#ifdef __BARE_METAL__
#include "wrapper_control.h"
#endif //__BARE_METAL__

// test results defines
#define TEST_SUCCESS 0
#define TEST_FAILED  1
#define TEST_NOTSUP  2

extern char errMsg[1024];

#define breakTestCustomString(...) \
    do { log_dbg_crit(__VA_ARGS__); \
         passed = TEST_FAILED; \
         goto done;} while (0)

#define markAsFailedCustomString(...) \
    do { log_dbg_crit(__VA_ARGS__); \
         passed = TEST_FAILED; \
         } while (0)

#define breakTest(...) \
    do { sprintf(errMsg, __VA_ARGS__); \
         log_dbg_crit("ERROR: %s, with error code: %u\n", errMsg, result); \
         passed = TEST_FAILED; \
         goto done;} while (0)

#define validateResult(expectedResult, ...) \
    do { if (result != (expectedResult)) { \
             breakTest(__VA_ARGS__);}} while (0)

#define validateNResult(faultResult, ...) \
    do { if (result == (faultResult)) { \
             breakTest(__VA_ARGS__);}} while (0)

#define validateSupport(...) \
    do { if (result == CDN_ENOTSUP) { \
             set_not_supported_reason(__VA_ARGS__); \
             goto done;}} while (0)

// This macro requires error_string to be complete (if you need arguments, use snprintf before)
#define eddTest(expected_return, error_string, emac_obj_number, api_function, ...) \
    do { result = emacObj[emac_obj_number]->api_function(privData[emac_obj_number], __VA_ARGS__);\
        validateResult(expected_return, error_string);\
        } while (0)

typedef struct {
    TestData td;
    char* name;
    char* notSupReason;
} CEDI_Drv_TestData;

extern CEDI_Drv_TestData d;
extern int passed;

void start_test(char *name);
void test_pass();
void test_fail();
void test_notsup();
void set_not_supported_reason(char *reason);
void test_init(char *group);
int end_test();

/* Pack of macros used to check values without break test */
#define compareUint(val, exp, testStr, varStr) \
    do { if (val != exp) { \
            log_dbg_crit("TEST ERROR! %s - %s = %u, expected %u\n", testStr, varStr, val, exp); \
            passed = TEST_FAILED;}} while (0)

#define compareXint(value, expected, testStr, varStr) \
    do { if (value != expected) { \
            log_dbg_crit("TEST ERROR! %s - %s = 0x%08X, expected 0x%08X\n", testStr, varStr, value, expected); \
            passed = TEST_FAILED;}} while(0)

/* Pack of macros used to check values with immediate break of test */
#define validateUint(val,exp,teststr,varstr) \
    do { if (val != exp) { log_dbg_crit("TEST ERROR! %s - %s = %u, expected %u\n", \
                                        teststr, varstr, val, exp); \
                           passed = TEST_FAILED; \
                           goto done;}} while (0)

#define validateXint(val,exp,teststr,varstr) \
    do { if (val != exp) {log_dbg_crit("TEST ERROR! %s - %s = 0x%08X, expected 0x%08X\n", \
                                       teststr, varstr, val, exp); \
                          passed = TEST_FAILED; \
                          goto done;}} while (0)

#define validateNUint(val,exp,teststr,varstr) \
    do { if (val == exp) {log_dbg_crit("TEST ERROR! %s - %s = %u, expected not equal to  %u\n", \
                                       teststr, varstr, val, exp); \
                          passed = TEST_FAILED; \
                          goto done;}} while (0)

#define validateTxRxTimeout(timeout, txStatus, rxStatus) \
    do { if (timeout == 0) { \
             if ((txStatus != 0) && (rxStatus == 0)) { \
                 log_dbg_fyi("Receive timed out.\n"); \
             } else if ((rxStatus == 0) && (txStatus == 0)) { \
                 log_dbg_fyi("Transmit timed out.\n"); \
             } else { \
                 log_dbg_fyi("Timeout - transmit not detected! (Rx OK)\n"); \
             } passed = TEST_FAILED; goto done;}} while (0)

#define word32val(wd32b) ((wd32b.byte3<<24)+(wd32b.byte2<<16)+(wd32b.byte1<<8)+wd32b.byte0)

#define byte0(uint) ((uint) & 0xFF)
#define byte1(uint) (((uint) & 0xFF00)>>8)
#define byte2(uint) (((uint) & 0xFF0000)>>16)
#define byte3(uint) (((uint) & 0xFF000000)>>24)

// setExtBDModeForAllQueues defines for clarity
#define TX_EXTBD_ENABLED  1U
#define TX_EXTBD_DISABLED 0U
#define RX_EXTBD_ENABLED  1U
#define RX_EXTBD_DISABLED 0U

/*#ifdef GEM0_REGS_BASE
 #define EMAC_REG_BASE_ADDRESS0  GEM0_REGS_BASE
 #define EMAC_REG_BASE_ADDRESS1  GEM1_REGS_BASE
 #endif

 #ifdef EMAC_GEM0_REGS_BASE
 #define EMAC_REG_BASE_ADDRESS0  EMAC_GEM0_REGS_BASE
 #define EMAC_REG_BASE_ADDRESS1  EMAC_GEM1_REGS_BASE
 #endif*/

#define RXQ_SIZE                (12)
#define TXQ_SIZE                (12)

/* Tx-Rx test result return values */
#define RX_TIMEOUT              (1002)
#define TX_OVERFLOW             (1003)
#define TX_TIMEOUT              (1004)
#define TX_TIMEOUT_RX_OK        (1005)

/* IP flags */
#define IP_FLAG_MF              (0x20)

#define MAX_TEST_RBQ_LENGTH (1000)

#define PREAMBLE_LEN        (8)

// setTimeStampingForAllQueues defines for clarity
#define TXTS_ENABLED  1U
#define TXTS_DISABLED 0U
#define RXTS_ENABLED  1U
#define RXTS_DISABLED 0U

#define MAX_QUEUES_NUM 16U

/* Ethernet frame structs */
/* simplest form, with Type/Len after source address */
typedef struct {
    CEDI_MacAddress dest;
    CEDI_MacAddress srce;
    uint8_t typeLenMsb;     /* ensure MSB-first format */
    uint8_t typeLenLsb;
} ethHdr_t;

/* VLan tag form, with VLAN tag after source address */
typedef struct {
    CEDI_MacAddress dest;
    CEDI_MacAddress srce;
    uint8_t vLanTpIdMsb;     /* ensure MSB-first format */
    uint8_t vLanTpIdLsb;
    uint8_t vLanTciMsb;
    uint8_t vLanTciLsb;
} ethHdr2_t;

/* Stacked VLan tag form, with two VLAN tags after source address */
typedef struct {
    CEDI_MacAddress dest;
    CEDI_MacAddress srce;
    uint8_t vLan1TpIdMsb;     /* ensure MSB-first format */
    uint8_t vLan1TpIdLsb;
    uint8_t vLan1TciMsb;
    uint8_t vLan1TciLsb;
    uint8_t vLan2TpIdMsb;
    uint8_t vLan2TpIdLsb;
    uint8_t vLan2TciMsb;
    uint8_t vLan2TciLsb;
} ethHdr3_t;

/** IPv4 address */
typedef struct {
    uint8_t byte[4];    /* byte[0] for first, i.e. top-level field */
} CEDI_IPv4Add;

/* IPv4 header */
typedef struct {
    uint8_t ihlVers;        /* = 0x54 */
    uint8_t dsCp;           /* lower 6 bits, ignoring ECN use of b6 & b7 */
    uint8_t lengthMsb;      /* min 20 for header only */
    uint8_t lengthLsb;
    uint16_t iD;            /* identification */
    uint16_t flgsFragOffset;
    uint8_t ttL;
    uint8_t prot;
    uint16_t hdrChksum;
    CEDI_IPv4Add srcAddr;
    CEDI_IPv4Add dstAddr;
} iPv4Hdr_t;

/* UDP header */
typedef struct {
    uint8_t srcPortMsb;        /* source port number */
    uint8_t srcPortLsb;
    uint8_t dstPortMsb;        /* destination port number */
    uint8_t dstPortLsb;
    uint8_t lengthMsb;         /* length inc. header */
    uint8_t lengthLsb;
    uint8_t chkSumMsb;         /* CRC of header+data */
    uint8_t chkSumLsb;
} udpHdr_t;

#pragma pack(push,1)    /* ensure byte-alignment for fields */
/* PTP frame, IPv4, 1588 v1 */
typedef struct {
    /* ethernet header */
    CEDI_MacAddress dest;       /* bytes 0-5 */
    CEDI_MacAddress srce;       /* bytes 6-11 */
    uint8_t typeLenMsb;         /* MSB = 0x08 */
    uint8_t typeLenLsb;         /* LSB = 0x00 */
    /* IP header */
    uint8_t ihlVers;            /* = 0x45     byte 14 */
    uint8_t dsCp;               /* byte 15 */
    uint8_t lengthMsb;          /* byte 16 */
    uint8_t lengthLsb;          /* byte 17 */
    uint16_t iD;                /* bytes 18-19 */
    uint16_t flgsFragOffset;    /* bytes 20-21 */
    uint8_t ttL;                /* byte 22 */
    uint8_t prot;               /* = 0x11, UDP   byte 23 */
    uint8_t hdrChksum[2];       /* bytes 24-25 */
    CEDI_IPv4Add srcAddr;       /* bytes 26-29 */
    CEDI_IPv4Add dstAddr;       /* = 0xE0000181/82/83/84) bytes 30-33 */
    /* UDP header */
    uint8_t srcPortMsb;         /* source port number   byte 34 */
    uint8_t srcPortLsb;         /* byte 35 */
    uint8_t dstPortMsb;         /* = 0x01   destination port number   byte 36 */
    uint8_t dstPortLsb;         /* = 0x3F      byte 37 */
    uint8_t udpLenMsb;          /* length inc. header    byte 38 */
    uint8_t udpLenLsb;          /* byte 39 */
    uint8_t chkSumMsb;          /* CRC of header+data     byte 40 */
    uint8_t chkSumLsb;          /* byte 41 */
    /* PTP message */
    uint8_t ptpVers[2];         /* version PTP  = 0x0001   bytes 42-43 */
    uint8_t netVers[2];         /* version network  bytes 44-45 */
    uint8_t subDom[16];         /* subdomain   bytes 46-61 */
    uint8_t msgTyp;             /* message type =0x01 for event, 0x02 for general  byte 62 */
    uint8_t srcTech;            /* source comms technology  byte 63 */
    uint8_t srcUuid[6];         /* source Uuid  byte 64-69 */
    uint8_t srcPort[2];         /* source port ID  bytes 70-71 */
    uint8_t seqId[2];           /* sequence ID    bytes 72-73 */
    uint8_t ptpCtrl;            /* = 0x00 for sync, 0x01 for dlyReq   byte 74 */
    uint8_t resvd3;             /* byte 75 */
    uint8_t flags[2];           /* bytes 76-77 */
    uint8_t resvd4[4];          /* bytes 78-81 */
    uint8_t timeSec[4];         /* timeStamp seconds   bytes 82-85 */
    uint8_t timeNsec[4];        /* timeStamp nanoseconds   bytes 86-89 */
    uint8_t padding[78];        /* fields for sync/delay_req formats   bytes 90-167 */
} ptpV1Frame;

/* PTP Event message frame, IPv4, 1588 v2 */
typedef struct {
    /* ethernet header */
    CEDI_MacAddress dest;       /* bytes 0-5 */
    CEDI_MacAddress srce;       /* bytes 6-11 */
    uint8_t typeLenMsb;         /* MSB = 0x08 */
    uint8_t typeLenLsb;         /* LSB = 0x00 */
    /* IP header */
    uint8_t ihlVers;            /* = 0x45     byte 14 */
    uint8_t dsCp;               /* byte 15 */
    uint8_t lengthMsb;          /* byte 16 */
    uint8_t lengthLsb;          /* byte 17 */
    uint16_t iD;                /* bytes 18-19 */
    uint16_t flgsFragOffset;    /* bytes 20-21 */
    uint8_t ttL;                /* byte 22 */
    uint8_t prot;               /* = 0x11, UDP   byte 23 */
    uint8_t hdrChksum[2];       /* bytes 24-25 */
    CEDI_IPv4Add srcAddr;       /* bytes 26-29 */
    CEDI_IPv4Add dstAddr;       /* = 0xE0000181/82/83/84) bytes 30-33 */
    /* UDP header */
    uint8_t srcPortMsb;         /* source port number   byte 34 */
    uint8_t srcPortLsb;         /* byte 35 */
    uint8_t dstPortMsb;         /* = 0x01   destination port number   byte 36 */
    uint8_t dstPortLsb;         /* = 0x3F      byte 37 */
    uint8_t udpLenMsb;          /* length inc. header    byte 38 */
    uint8_t udpLenLsb;          /* byte 39 */
    uint8_t chkSumMsb;          /* CRC of header+data     byte 40 */
    uint8_t chkSumLsb;          /* byte 41 */
    /* PTP message header */
    uint8_t trSpec_MsgType;     /* transport-specific upper nibble, messageType lower nibble:
                                   00 for sync, 02 for Pdelay_req, 03 for Pdelay_resp  byte 42 */
    uint8_t ptpVers;            /* = 0x02   byte 43 */
    uint8_t msgLenMsb;          /* length of PTP message, =34 bytes + message after header  bytes 44-45 */
    uint8_t msgLenLsb;
    uint8_t domNum;             /* domain number    byte 46 */
    uint8_t resvd1;             /* byte 47 */
    uint8_t flagField[2];       /* bytes 48-49 */
    uint8_t correct[8];         /* correction field   bytes 50-57 */
    uint8_t resvd2[4];          /* bytes 58-61 */
    uint8_t srcPrtId[10];       /* source port identity   bytes 62-71 */
    uint8_t seqId[2];           /* sequence ID    bytes 72-73 */
    uint8_t control;            /* control, dep on msgType   byte 74 */
    uint8_t logMsgInt;          /* log message interval   byte 75 */
    /* PTP Event message */
    uint8_t timestamp[10];      /* origin/receive timestamp      bytes 76-85 */
    uint8_t reqPortId[10];      /* used for delay_resp/pdelay_resp formats   bytes 86-95*/
} ptpV2Frame;

typedef struct {
    CEDI_MacAddress dest;
    CEDI_MacAddress srce;
    uint8_t typeLenMsb;     /* = 0x88 type: MAC control frame */
    uint8_t typeLenLsb;     /* = 0x08 */
    uint8_t opcodeMsb;      /* = 0x00 Pause opcode */
    uint8_t opcodeLsb;      /* = 0x01 */
    uint8_t pauseTimeMsb;
    uint8_t pauseTimeLsb;
    uint8_t padding[46];
} pauseFr_t;

/* 32-bit word struct as bytes - MSByte first, ie. tx order */
typedef struct {
    uint8_t byte3;
    uint8_t byte2;
    uint8_t byte1;
    uint8_t byte0;
} word32b_t;

/* basic TCP frame, IPv4 */
typedef struct {
    /* ethernet header */
    CEDI_MacAddress dest;       /* bytes 0-5 */
    CEDI_MacAddress srce;       /* bytes 6-11 */
    uint8_t     typeLenMsb;     /* MSB = 0x08   byte 12 */
    uint8_t     typeLenLsb;     /* LSB = 0x00   byte 13 */
    /* IP header */
    uint8_t     ihlVers;        /* = 0x45     byte 14 */
    uint8_t     dsCp;           /* byte 15 */
    uint8_t     frLengthMsb;    /* byte 16 */
    uint8_t     frLengthLsb;    /* byte 17 */
    uint8_t     idMsb;          /* byte 18 */
    uint8_t     idLsb;          /* byte 19 */
    uint8_t     flgsFrOffsMsb;  /* IP Flags, b7-b5, fragment offset MSB b4-b0  byte 20 */
    uint8_t     fragOffsLsb;    /* fragment offset LSB  byte 21 */
    uint8_t     ttL;            /* byte 22 */
    uint8_t     prot;           /* = 0x06, TCP   byte 23 */
    uint8_t     hdrChksumMsb;   /* byte 24 */
    uint8_t     hdrChksumLsb;   /* byte 25 */
    CEDI_IPv4Add srcIpAddr;     /* byte 26-29 */
    CEDI_IPv4Add dstIpAddr;     /* byte 30-33 */
    /* TCP header */
    uint8_t     srcPortMsb;     /* source port number  byte 34 */
    uint8_t     srcPortLsb;     /* source port number  byte 35 */
    uint8_t     dstPortMsb;     /* destination port number  byte 36 */
    uint8_t     dstPortLsb;     /* destination port number  byte 37 */
    word32b_t   seqNum;         /* sequence number  bytes 38-41 */
    word32b_t   ackNum;         /* ACK number       bytes 42-45 */
    uint8_t     datOffsFlgsMsb; /* TCP flags MSB (b1),  Data offset bits 7-4  byte 46 */
    uint8_t     tcpFlagsLsb;    /* TCP flags LSB   byte 47 */
    uint8_t     windowSizeMsb;  /* byte 48 */
    uint8_t     windowSizeLsb;  /* byte 49 */
    uint8_t     tcpChksumMsb;   /* byte 50 */
    uint8_t     tcpChksumLsb;   /* byte 51 */
    uint8_t     urgentPtrMsb;   /* byte 52 */
    uint8_t     urgentPtrLsb;   /* byte 53 */
} tcpHeader1_t;

/* basic UDP frame, IPv4 */
typedef struct {
    /* ethernet header */
    CEDI_MacAddress dest;       /* bytes 0-5 */
    CEDI_MacAddress srce;       /* bytes 6-11 */
    uint8_t     typeLenMsb;     /* MSB = 0x08 */
    uint8_t     typeLenLsb;     /* LSB = 0x00 */
    /* IP header */
    uint8_t     ihlVers;        /* = 0x45   byte 14 */
    uint8_t     dsCp;           /* byte 15 */
    uint8_t     frLengthMsb;    /* byte 16 */
    uint8_t     frLengthLsb;    /* byte 17 */
    uint8_t     idMsb;          /* byte 18 */
    uint8_t     idLsb;          /* byte 19 */
    uint8_t     flgsFrOffsMsb;  /* byte 20 */
    uint8_t     fragOffsLsb;    /* byte 21 */
    uint8_t     ttL;            /* byte 22 */
    uint8_t     prot;           /* = 0x11, UDP   byte 23 */
    uint8_t     hdrChksumMsb;   /* byte 24 */
    uint8_t     hdrChksumLsb;   /* byte 25 */
    CEDI_IPv4Add srcIpAddr;     /* bytes 26-29 */
    CEDI_IPv4Add dstIpAddr;     /* bytes 30-33 */
    /* UDP header */
    uint8_t     srcPortMsb;     /* source port number  byte 34 */
    uint8_t     srcPortLsb;     /* source port number  byte 35 */
    uint8_t     dstPortMsb;     /* destination port number  byte 36 */
    uint8_t     dstPortLsb;     /* destination port number  byte 37 */
    uint8_t     udpLengthMsb;   /* UDP header+data  byte 38 */
    uint8_t     udpLengthLsb;   /* UDP header+data  byte 39 */
    uint8_t     udpChksumMsb;   /* byte 40 */
    uint8_t     udpChksumLsb;   /* byte 41 */
} udpHeader1_t;

/* initTcpUdpHeader parameters - for UDP or TCP header */
typedef struct {
    CEDI_MacAddress srcMac;
    CEDI_MacAddress dstMac;
    uint16_t dataLen;
    uint16_t id;
    CEDI_IPv4Add srcIpAddr;
    CEDI_IPv4Add dstIpAddr;
    uint16_t srcPort;           /* TCP or UDP */
    uint16_t dstPort;           /* TCP or UDP */
    uint32_t seqNum;            /* TCP */
    uint32_t ackNum;            /* TCP */
    uint16_t flags;             /* TCP */
    uint16_t window;            /* TCP */
    uint16_t udpLength;         /* UDP */
    uint16_t udpChksum;         /* UDP */
} tcpUdpParams_t;

#endif //INCLUDE_EDD_COMMON_H
