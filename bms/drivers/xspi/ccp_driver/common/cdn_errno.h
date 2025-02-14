/******************************************************************************
 * Copyright (C) 2014-2020 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * cdn_errno.h
 * Cadence error codes
 ******************************************************************************
 */

#ifndef INCLUDE_CDN_ERRNO_H
#define INCLUDE_CDN_ERRNO_H

#define CDN_EOK             0U      /* no error */

#define CDN_EPERM           1U      /* Operation not permitted */

#define CDN_ENOENT          2U      /* No such file or directory */

#define CDN_EIO             5U      /* I/O error */

#define CDN_ENOEXEC         8U      /* Exec format error */

#define CDN_EAGAIN          11U      /* Try again */

#define CDN_ENOMEM          12U      /* Out of memory */

#define CDN_EFAULT          14U      /* Bad address */

#define CDN_EBUSY           16U      /* Device or resource busy */

#define CDN_EINVAL          22U      /* Invalid argument */

#define CDN_ENOSPC          28U      /* No space left on device */

#define CDN_EBADSLT         57U      /* Invalid slot */

#define CDN_EPROTO          71U      /* Protocol error */

#define CDN_EOVERFLOW       75U      /* Value too large for defined data type */

#define CDN_EOPNOTSUPP      95U      /* Operation not supported */

#define CDN_ETIMEDOUT       110U     /* Connection timed out */

#define CDN_EINPROGRESS     115U     /* Operation now in progress */

#define CDN_EDQUOT          122U     /* Quota exceeded */

#define CDN_ENOTSUP         CDN_EOPNOTSUPP

#define CDN_ECANCELED       126U      /* Cancelled */

#endif //INCLUDE_CDN_ERRNO_H
