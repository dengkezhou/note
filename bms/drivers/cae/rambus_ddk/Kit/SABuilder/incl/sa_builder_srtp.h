/* sa_builder_srtp.h
 *
 * SRTP specific functions of the SA Builder.
 */

/*****************************************************************************
* Copyright (c) 2011-2020 by Rambus, Inc. and/or its subsidiaries.
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


#ifndef  SA_BUILDER_SRTP_H_
#define SA_BUILDER_SRTP_H_


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

#include "sa_builder_params.h"
#include "sa_builder.h"
#include "sa_builder_params_srtp.h"

// Driver Framework Basic Definitions API
#include "basic_defs.h"


/*----------------------------------------------------------------------------
 * SABuilder_Init_SRTP
 *
 * This function initializes the SABuilder_Params_t data structure and
 * its SABuilder_Params_SRTP_t extension with sensible defaults for
 * SRTP processing..
 *
 * SAParams_p (output)
 *   Pointer to SA parameter structure to be filled in.
 * SAParamsSRTP_p (output)
 *   Pointer to SRTP parameter extension to be filled in
 * IsSRTCP (input)
 *   true if the SA is for SRTCP.
 * direction (input)
 *   Must be one of SAB_DIRECTION_INBOUND or SAB_DIRECTION_OUTBOUND.
 *
 * Tis function initializes the authentication algorithm to HMAC_SHA1.
 * The application has to fill in the appropriate keys. The crypto algorithm
 * is initialized to NULL. It can be changed to AES ICM and then a crypto
 * key has to be added as well.
 *
 * Both the SAParams_p and SAParamsSRTP_p input parameters must point
 * to valid storage where variables of the appropriate type can be
 * stored. This function initializes the link from SAParams_p to
 * SAParamsSRTP_p.
 *
 * Return:
 * SAB_STATUS_OK on success
 * SAB_INVALID_PARAMETER when one of the pointer parameters is NULL
 *   or the remaining parameters have illegal values.
 */
SABuilder_Status_t
SABuilder_Init_SRTP(
    SABuilder_Params_t * const SAParams_p,
    SABuilder_Params_SRTP_t * const SAParamsSRTP_p,
    const bool IsSRTCP,
    const SABuilder_Direction_t direction);


#endif /* SA_BUILDER_SRTP_H_ */


/* end of file sa_builder_srtp.h */
