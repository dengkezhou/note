/******************************************************************************
 * Copyright (C) 2013-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * sdio_dma.h
 * SD Host controller driver DMA module
 *****************************************************************************/

#ifndef SDIO_DMA_H
#define SDIO_DMA_H

#include "sdio_types.h"

/*****************************************************************************/
/*!
 * @fn      uint8_t DMA_PrepareTransfer(CSDD_SDIO_Slot* pSlot,
 *                                  CSDD_Request* pRequest)
 * @brief       Function prepare DMA module to data transfer
 * @param       pSlot Slot on which the DMA transfer shall be execute
 * @param       pRequest it describes request to execute
 * @return      Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t DMA_PrepareTransfer(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest);

/*****************************************************************************/
/*!
 * @fn      uint8_t DMA_PrepareTransfer(CSDD_SDIO_Slot* pSlot,
 *                                  CSDD_Request* pRequest)
 * @brief   Function handles DMA interrupt
 * @param   pSlot Slot on which DMA interrupt occured
 * @param   pRequest it describes request which
 *              is currently executed
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t DMA_HandleInterrupt(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest, uint32_t Status);

/*****************************************************************************/
/*!
 * @fn      uint8_t DMA_FinishTransfer(CSDD_SDIO_Slot* pSlot,
 *                                  CSDD_Request* pRequest)
 * @brief   Function finishes DMA transfer
 * @param   pSlot Slot on which the DMA transfer is executing
 * @param   pRequest it describes executing request
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t DMA_FinishTransfer(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest);

/*****************************************************************************/
/*!
 * @fn      uint8_t DMA_FinishTransfer(CSDD_SDIO_Slot* pSlot,
 *                                  CSDD_Request* pRequest)
 * @brief   Function selects optimal DMA transmission mode
 * @param   pSlot Slot on which the DMA transfer shall be execute
 * @param   pRequest it describes request to execute
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t DMA_SpecifyTransmissionMode(CSDD_SDIO_Slot* pSlot, CSDD_Request* pRequest);

#endif
