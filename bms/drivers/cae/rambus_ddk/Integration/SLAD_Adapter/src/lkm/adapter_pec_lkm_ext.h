/* adapter_pec_lkm_ext.h
 *
 * PEC API implementation,
 * Linux kernel specific extensions
 *
 */

/*****************************************************************************
* Copyright (c) 2012-2020 by Rambus, Inc. and/or its subsidiaries.
* All rights reserved. Unauthorized use (including, without limitation,
* distribution and copying) is strictly prohibited. All use requires,
* and is subject to, explicit written authorization and nondisclosure
* Rambus, Inc. and/or its subsidiaries
*
* For more information or support, please go to our online support system at
* https://sipsupport.rambus.com.
* In case you do not have an account for this system, please send an e-mail
* to sipsupport@rambus.com.
*****************************************************************************/

#ifndef ADAPTER_PEC_LKM_EXT_H_
#define ADAPTER_PEC_LKM_EXT_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Top-level Adapter configuration
#include "cs_adapter.h"

// Linux Kernel API
//#include <linux/init.h>     // module_init, module_exit
//#include <linux/module.h>   // EXPORT_SYMBOL


/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include "api_pec.h"        // PEC API

#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
#include "api_pec_sg.h"     // PEC SG API
#endif /* ADAPTER_PEC_ENABLE_SCATTERGATHER */

#include "iotoken.h"        // IOToken API

// PEC API
//EXPORT_SYMBOL(PEC_Capabilities_Get);
//EXPORT_SYMBOL(PEC_Init);
//EXPORT_SYMBOL(PEC_UnInit);
//EXPORT_SYMBOL(PEC_SA_Register);
//EXPORT_SYMBOL(PEC_SA_UnRegister);
//EXPORT_SYMBOL(PEC_Packet_Put);
//EXPORT_SYMBOL(PEC_Packet_Get);
//EXPORT_SYMBOL(PEC_CommandNotify_Request);
//EXPORT_SYMBOL(PEC_ResultNotify_Request);
//EXPORT_SYMBOL(PEC_CD_Control_Write);
//EXPORT_SYMBOL(PEC_RD_Status_Read);
//EXPORT_SYMBOL(PEC_Put_Dump);
//EXPORT_SYMBOL(PEC_Get_Dump);

#ifdef ADAPTER_PEC_ENABLE_SCATTERGATHER
EXPORT_SYMBOL(PEC_SGList_Create);
EXPORT_SYMBOL(PEC_SGList_Destroy);
EXPORT_SYMBOL(PEC_SGList_Write);
EXPORT_SYMBOL(PEC_SGList_Read);
EXPORT_SYMBOL(PEC_SGList_GetCapacity);
EXPORT_SYMBOL(PEC_Scatter_Preload);
EXPORT_SYMBOL(PEC_Scatter_PreloadNotify_Request);
#endif /* ADAPTER_PEC_ENABLE_SCATTERGATHER */

// IOToken API
//EXPORT_SYMBOL(IOToken_Create);
//EXPORT_SYMBOL(IOToken_Parse);
//EXPORT_SYMBOL(IOToken_InWordCount_Get);
//EXPORT_SYMBOL(IOToken_OutWordCount_Get);
//EXPORT_SYMBOL(IOToken_SAAddr_Update);
//EXPORT_SYMBOL(IOToken_SAReuse_Update);
//EXPORT_SYMBOL(IOToken_Mark_Set);
//EXPORT_SYMBOL(IOToken_Mark_Check);
//EXPORT_SYMBOL(IOToken_PacketLegth_Get);
//EXPORT_SYMBOL(IOToken_BypassLegth_Get);
//EXPORT_SYMBOL(IOToken_ErrorCode_Get);


#endif // ADAPTER_PEC_LKM_EXT_H_


/* end of file adapter_pec_lkm_ext.h */
