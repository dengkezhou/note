/* eip202_rdr_dscr.h
 *
 * EIP-202 Ring Control Driver Library API Result Descriptor Internal interface
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

#ifndef EIP202_RDR_DSCR_H_
#define EIP202_RDR_DSCR_H_


/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */



/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * Definitions and macros
 */


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * EIP202_RDR_WriteCB
 * A write callback for the Ring Helper
 */
int
EIP202_RDR_WriteCB(cae_device *dev,
        void * const CallbackParam1_p,
        const int CallbackParam2,
        const unsigned int WriteIndex,
        const unsigned int WriteCount,
        const unsigned int TotalWriteLimit,
        const void * Descriptors_p,
        const int DescriptorCount,
        const unsigned int DescriptorSkipCount);


/*----------------------------------------------------------------------------
 * EIP202_RDR_ReadCB
 * A read callback for the Ring Helper
 */
int
EIP202_RDR_ReadCB(cae_device *dev,
        void * const CallbackParam1_p,
        const int CallbackParam2,
        const unsigned int ReadIndex,
        const unsigned int ReadLimit,
        void * Descriptors_p,
        const unsigned int DescriptorSkipCount);


/*----------------------------------------------------------------------------
 * EIP202_RDR_StatusCB
 * A status callback for the Ring Helper
 */

int
EIP202_RDR_StatusCB(cae_device *dev,
        void * const CallbackParam1_p,
        const int CallbackParam2,
        int * const DeviceReadPos_p);


#endif /* EIP202_RDR_DSCR_H_ */


/* end of file eip202_rdr_dscr.h */
