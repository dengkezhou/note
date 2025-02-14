/* parasoft suppress item  MISRA2012-DIR-4_8 "Consider hiding implementation of
 * structure, DRV-4932" */
/**********************************************************************
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************
 * WARNING: This file is auto-generated using api-generator utility.
 *          api-generator: 13.05.b3ee589
 *          Do not edit it manually.
 **********************************************************************
 * Add comment
 **********************************************************************/
#ifndef LIST_STRUCTS_IF_H
#define LIST_STRUCTS_IF_H

#include "cdn_stdtypes.h"
#include "list_if.h"

/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
 * Structures and unions
 **********************************************************************/
/** . */
struct LIST_ListHead_s {
  /** pointer to next element in list */
  LIST_ListHead *next;
  /** pointer to previous element in list */
  LIST_ListHead *prev;
};

/**
 *  @}
 */

#endif /* LIST_STRUCTS_IF_H */
