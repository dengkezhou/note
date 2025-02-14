/* cs_umdevxsproxy.h
 *
 * Configuration options for UMDevXS Proxy Library.
 *
 */

/*****************************************************************************
* Copyright (c) 2010-2020 by Rambus, Inc. and/or its subsidiaries.
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

#ifndef INCLUDE_GUARD_CS_UMDEVXSPROXY_H
#define INCLUDE_GUARD_CS_UMDEVXSPROXY_H

//#define UMDEVXSPROXY_REMOVE_SMBUF

//#define UMDEVXSPROXY_REMOVE_INTERRUPT

#define UMDEVXSPROXY_NODE_NAME "/dev/umpci_c"

#define UMDEVXSPROXY_REMOVE_DEVICE_FIND
#define UMDEVXSPROXY_REMOVE_DEVICE_ENUM
#define UMDEVXSPROXY_REMOVE_DEVICE_UNMAP
#define UMDEVXSPROXY_REMOVE_SMBUF_ATTACH
#define UMDEVXSPROXY_REMOVE_SMBUF_COMMIT

#endif /* INCLUDE_GUARD_CS_UMDEVXSPROXY_H */


/* end of file cs_umdevxsproxy.h */
