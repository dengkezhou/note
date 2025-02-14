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
 * sdio_phy.h
 * SD Host controller driver - PHY module
 *****************************************************************************/

#ifndef SDIO_PHY_H
#define SDIO_PHY_H

#include "sdio_types.h"

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIO_Phy_PhySettings_SDv4(const CSDD_SDIO_Host* pSdioHost,
 *			    const CSDD_PhyDelaySettings *PhyDelaySet)
 * @brief   Function sets configures delay line in UHS-I PHY hardware module.
 *		Function works for SD Host 4
 * @param   pSdioHost pointer to sdio host object
 * @param   PhyDelaySet PHY delay settings
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIO_Phy_PhySettings_SDv4(const CSDD_SDIO_Host*             pSdioHost,
                                  const CSDD_PhyDelaySettings *PhyDelaySet);

/*****************************************************************************/
/*!
 * @fn      uint8_t SDIO_Phy_PhySettings_SDv4(const CSDD_SDIO_Host* pSdioHost,
 *			    const CSDD_PhyDelaySettings *PhyDelaySet)
 * @brief   Function sets configures delay line in UHS-I PHY hardware module.
 *		Function works for SD Host 3
 * @param   pSlot pointer to sdio slot object
 * @param   PhyDelaySet PHY delay settings
 * @return  Function returns 0 if everything is ok
 *              otherwise returns error number
 */
/*****************************************************************************/
uint8_t SDIO_Phy_PhySettings_SDv3(const CSDD_SDIO_Slot*             pSlot,
                                  const CSDD_PhyDelaySettings *PhyDelaySet);

uint8_t SDIO_ReadPhySet(const CSDD_SDIO_Host* pSdioHost, uint8_t slotIndex,
                        CSDD_PhyDelay delayType, uint8_t *delayVal);

uint8_t SDIO_WritePhySet(const CSDD_SDIO_Host* pSdioHost, uint8_t slotIndex,
                         CSDD_PhyDelay delayType, uint8_t delayVal);

uint32_t SDIO_CPhy_DLLReset(CSDD_SDIO_Host* pSdioHost, bool doReset);

void SDIO_CPhy_SetCPhyConfigIoDelay(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigIoDelay* ioDelay);
void SDIO_CPhy_GetCPhyConfigIoDelay(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigIoDelay* ioDelay);
void SDIO_CPhy_SetConfigLvsi(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigLvsi* lvsi);
void SDIO_CPhy_GetConfigLvsi(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigLvsi* lvsi);
void SDIO_CPhy_SetConfigDfiRd(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigDfiRd* dfiRd);
void SDIO_CPhy_GetConfigDfiRd(CSDD_SDIO_Host* pSdioHost, CSDD_CPhyConfigDfiRd* dfiRd);
void SDIO_CPhy_SetConfigOutputDelay(CSDD_SDIO_Host* pSdioHost,
                                       CSDD_CPhyConfigOutputDelay* outputDelay);
void SDIO_CPhy_GetConfigOutputDelay(CSDD_SDIO_Host* pSdioHost,
                                       CSDD_CPhyConfigOutputDelay* outputDelay);
void SDIO_CPhy_SetExtMode(CSDD_SDIO_Host* pSdioHost, bool extendedWrMode,
                             bool extendedRdMode);
void SDIO_CPhy_GetExtMode(CSDD_SDIO_Host* pSdioHost, bool* extendedWrMode,
                             bool* extendedRdMode);
void SDIO_CPhy_SetSdclkAdj(CSDD_SDIO_Host* pSdioHost, uint8_t sdclkAdj);
void SDIO_CPhy_GetSdclkAdj(CSDD_SDIO_Host* pSdioHost, uint8_t* sdclkAdj);

#endif
