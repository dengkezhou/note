/**********************************************************************
 * Copyright (C) 2018-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************/
#ifndef INCLUDE_EDD_SUPPORT_H
#define INCLUDE_EDD_SUPPORT_H

#include "cdn_errno.h"
#include "cdn_stdint.h"
#include "cps.h"

#include "edd_data.h"
#include "edd_common.h"
#include "edd_int.h"

#define CEDI_READ_ISR_QN_CASE(Q) \
case Q: result = CPS_UncachedRead32(regAddr(emacA, int_q ## Q ## _status)); break;

#define IN_TOLERANCE(value, exp, tol, min, max) \
    ((value >= (((exp - tol) < min) ? min : (exp - tol))) && (value <= (((exp + tol) > max) ? max : (exp + tol))))

/* from cps_udr_ */
long NCPS_allocHWMem(uint32_t size);
long NCPS_freeHWMem(uintptr_t addr);

/**
 * Intialise a CEDI_Config structure for specified GEM instance, using
 * values specified by parameters
 * @param cInst CDDC instance, for debug output
 * @param objInst GEM instance: 0 or 1
 * @param numQs - number of queues
 * @param txQSize - number of descriptors per Tx queue
 * @param rxQSize - number of descriptors per Rx queue
 * @param rxBufLenBytes - size of Rx buffers to use
 * @param intrEvents - events to enable on start API call
 * @param cfg - pointer to config struct to initialise
 * @return 0 if successful
 * @return EINVAL if invalid parameter
 */
uint32_t initConfig(uint8_t objInst, uint8_t numQs,
                    uint16_t txQSize, uint16_t rxQSize,
                    uint16_t rxBufLenBytes, uint32_t intrEvents,
                    CEDI_Config *cfg);

/**
 * Intialise a CEDI_Config structure for specified GEM instance, using
 * maximum available Tx & Rx queues, and other values specified by parameters
 * @param cInst CDDC instance, for debug output
 * @param objInst GEM instance: 0 or 1
 * @param txQSize - number of descriptors per Tx queue
 * @param rxQSize - number of descriptors per Rx queue
 * @param rxBufLenBytes - size of Rx buffers to use
 * @param intrEvents - events to enable on start API call
 * @param cfg - pointer to config struct to initialise
 * @return 0 if successful
 * @return EINVAL if invalid parameter
 */
uint32_t initConfigMaxNumQs(uint8_t objInst, uint16_t txQSize,
                            uint16_t rxQSize,uint16_t rxBufLenBytes,
                            uint32_t intrEvents, CEDI_Config *cfg);

/**
 * Initialisation of driver for one of the two GEM instances in the VSP test
 * wrapper.
 * Calls probe and init functions to provide inital setup for test cases.
 * Test can either provide a specific configuration (used for both instances),
 * or if cfgPtr==NULL, the initConfig function will be used as a standard
 * initialisation, using the txQSize, rxQSize and rxBufLenBytes parameters.
 * In this case, the maximum number of Tx & Rx queues will be configured.
 * If PCS is present and MII/GMII interface selected, this will be changed to
 * 1000BASE_X.
 *
 * @param cInst CDDC instance, for debug output
 * @param objInst GEM instance: 0 or 1
 * @param txQSize - number of descriptors per Tx queue, used if cfgPtr==NULL
 * @param rxQSize - number of descriptors per Rx queue, used if cfgPtr==NULL
 * @param rxBufLenBytes - size of Rx buffers to use, if cfgPtr==NULL
 * @param cfgPtr - defines the configuration to initialise the driver and h/w
 * @return 0 for success
 * @return 1 if probe call returns error or private data malloc fails
 * @return 2 if Rx descriptors' HWMem alloc fails
 * @return 3 if Tx descriptors' HWMem alloc fails
 * @return 4 if init call returns error
 */
uint32_t testSetup(uint8_t ojbInst, uint16_t txQSize,
                   uint16_t rxQSize, uint16_t rxBufLenBytes, CEDI_Config *cfgPtr);

/**
 * Destroy the driver object and free up memory reserved by testSetup
 * @param cInst CDDC instance, for debug output
 * @param objInst GEM instance: 0 or 1
 */
void testTearDown(uint8_t objInst);

/**
 * Allocate a kernel buffer, fill with an incrementing data pattern and return
 * virtual & physical addresses
 * @param[in] bytes number of bytes to fill
 * @param[in] fill pattern used to fill buffer
 * @param[out] buf pointer to buffer
 * @return CDN_EOK if success or CDN_EINVAL if buffer address not aligned
 */
uint32_t allocBuffer(uint32_t bytes, uint32_t fill, CEDI_BuffAddr *buf);

/**
 * Transmit & receive 1 frame in single buffer using polling methods.
 * Isr still called in order to detect error callbacks; it is expected that
 * test will disable Tx complete, Tx used bit read and Rx complete events
 * before calling txRxPollTestFrame.
 *
 * @param emacTx GEM instance for Tx: 0 or 1
 * @param txDat pointer to byte-buffer containing frame to transmit, including
 *               header if required (auto-CRC is used)
 * @param txLen length of data in txDat
 * @param emacRx GEM instance for Rx: 0 or 1, must be opposite of emacTx
 * @param rxDat pointer to byte-buffer for returning received frame
 * @param rxLen pointer for returning length of received frame
 * @param rxdStat pointer for returning frame Rx descriptor status
 * @param toutCount timeout count for tx-rx loop (arbitrary units)
 * @return 0 if successful
 * @return 1001 if fail to allocate Tx DMA buffer
 * @return 1004 if frame length too long for Tx in current configuration
 * @return 1002 if timeout from tx-rx loop
 * @return 1005 if Rx data doesn't match Tx data
 * @return 1 for various errors: queueTxBuf/rxReadBuf fails, incorrect Rx
 *          buffer status, Rx buffer allocation, Rx descriptor list too short,
 *          unexpected event callback
 */
uint32_t txRxPollTestFrame(int emacTx, uint8_t *txDat, uint32_t txLen,
                           int emacRx, uint8_t *rxDat, uint32_t *rxLen,
                           CEDI_RxDescStat *rxdStat, uint32_t toutCount);

/**
 * Do common preparation of two initialised GEM driver instances for tx-rx
 * testing.
 * Prepare Rx descriptors - allocate buffers to Rx descriptor lists,
 * (tracked in aBuf[]) and spare buffer for swapping (nBuf[]), and enable Tx/Rx
 * @param emacTx GEM instance for Tx: 0 or 1
 * @param emacRx GEM instance for Rx: 0 or 1, must be opposite of emacTx
 * @return 0 if successful
 * @return 1001 if error
 */
uint32_t prepareTxRx(uint8_t emacTx, uint8_t emacRx);

/**
 * Stop Tx & Rx, free buffers reserved by prepareTxRx
 * @param emacTx GEM instance for Tx: 0 or 1
 * @param emacRx GEM instance for Rx: 0 or 1, must be opposite of emacTx
 */
void freeBuffersStopTxRx(uint8_t emacTx, uint8_t emacRx);

/**
 * Transmit & receive 1 frame using isr()/event callbacks, frame passed in byte-buffer
 * rxDat, and returned in txDat
 * @param cInst CDDC instance, for debug output
 * @param emacTx GEM instance for Tx: 0 or 1
 * @param txDat pointer to byte-buffer containing frame to transmit, including
 *               header if required (auto-CRC is used)
 * @param txLen length of data in txDat
 * @param autoCrc select whether to use auto-CRC
 * @param emacRx GEM instance for Rx: 0 or 1, must be opposite of emacTx
 * @param rxDat pointer to byte-buffer for returning received frame
 * @param rxLen pointer for returning length of received frame
 * @param rxdStat pointer for returning frame Rx descriptor status
 * @param rxBufsExp pointer for returning number of Rx buffers used
 * @return 0 if successful
 * @return 1000 if getFcsRemove call fails
 * @return 1001 if fail to allocate Tx DMA buffer
 * @return RX_TIMEOUT if Rx timeout from tx-rx loop
 * @return TX_TIMEOUT if Tx timeout from tx-rx loop
 * @return TX_TIMEOUT_RX_OK if Tx-not-detected timeout from tx-rx loop
 * @return TX_OVERFLOW if Tx overflow (frame corruption) error
 * @return 1 for various errors: queueTxBuf/rxReadBuf fails, Rx buffer
 *          allocation, Rx descriptor list too short, Rx data doesn't match Tx
 *          data, unexpected event callback
 */
uint32_t txRxEventTestFrame(uint8_t emacTx, uint8_t *txDat, uint32_t txLen, uint8_t autoCrc,
                            uint8_t emacRx, uint8_t *rxDat, uint32_t *rxLen,
                            CEDI_RxDescStat *rxdStat, uint16_t *rxBufsExp);

/**
 * Function initialize emacA and emacB, allocate buffers and send data from each
 * Tx queue.
 * @param[in] emacA GEM instance for Tx
 * @param[in] emacB GEM instance for Rx
 * @param[in] numQs number of tested Queues
 * @param[in] txLen number of bytes in Tx buffer
 * @param[out] passPtr test status
 * @return CDN_EOK if function was called properly
 * @return other error code if fail
 */
uint32_t doTxAndValidate(const int emacA, const int emacB, uint32_t numQs,uint32_t txLen);

/**
 * Initialise a combined basic IPv4 TCP (no Options) or UDP header with
 * supplied field values
 * udpNotTcp ==0 for TCP, !=0 for UDP
 */
void initTcpUdpHeader(tcpUdpParams_t *prm, uint8_t udpNotTcp, void *hdr);

/* Check TCP frame correctness
 * Return 0 if correct or 1 if incorrect
 */
uint32_t validateRxTcpFrame(char *tstFrStr, tcpHeader1_t *txTcpHdr, tcpHeader1_t *rxTcpHdr,
                            uint8_t skipSeqAckChksum, uint16_t txInd, uint16_t rxInd, uint16_t datLen);

/* Read single Rx buffer for header/data split test: assume one buffer for
 * header and only one for data.
 * @return 1 if success, 0 if fails
 */
uint32_t readOneRxBuf(int emacRx, uint8_t qNum, uint8_t *bufNum,
                      CEDI_RxDescStat *rxdStat, uint32_t *toutCount,
                      uint16_t *rxLen, uint8_t *rxDat);

/* Returns if is 2p5G speed is supported by module */
bool is2p5GSupported(uint8_t mac);

uint32_t sendAndValidateDSframes(const int emacA, const int emacB, uint8_t numQs );

uint32_t setScrnT2Reg(const int emac, CEDI_MacAddress SrcAddr, uint8_t screenReg, uint8_t compReg, uint8_t queueNum);

void Idle();

void insertEthHeader(ethHdr_t* header, CEDI_BuffAddr* buffer);

uint32_t detectCallback(uint8_t gem);

uint8_t cfgHwQs(uint8_t emacInst);

uint32_t checkResult(uint8_t expRxOk, uint8_t expTxOk, uint8_t rxOk, uint8_t txOk, uint32_t t);

void setExtBDModeForAllQueues(CEDI_Config *cfg, uint8_t tx_extbd_enable, uint8_t rx_extbd_enable);

uint32_t allocSysReqMem(uint8_t objInst, CEDI_SysReq *req,CEDI_Config *cfg);

void zeroCallbackCounters(void);

void loopDelay(uint32_t loops);

uint32_t compareRxDescFlags(uint8_t emacInst, uint8_t numQ, uint16_t index,
                            uint8_t used, uint8_t wrap, uint8_t sof, uint8_t eof);

uint32_t getRxDescBufAddr(uint8_t emacInst, uint8_t numQ, uint16_t index);

void DoTxRxFrame(int emacA, int emacB, uint32_t txLen,
                 uint8_t rxQ, int *passedPtr, uint8_t *rxOk, uint8_t *txOk,
                 uint32_t *timeout);
#endif //INCLUDE_EDD_SUPPORT_H
