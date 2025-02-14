/******************************************************************************
 *
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * sduc_list.h
 * Functions for creating and management circular list
 ******************************************************************************/

#ifndef CDN_LIST_H
#define CDN_LIST_H

#include "list_if.h"
#include "list_structs_if.h"

/*Function initialize list*/
static inline void listInit(LIST_ListHead *list) {
  list->next = list;
  list->prev = list;
}

/*Add new element to the list between prev and next*/
static inline void listAddElement(LIST_ListHead *item, LIST_ListHead *prev,
                                  LIST_ListHead *next) {
  next->prev = item;
  item->next = next;
  item->prev = prev;
  prev->next = item;
}

/*Add new entry after a specified head*/
static inline void listAdd(LIST_ListHead *item, LIST_ListHead *head) {
  listAddElement(item, head, head->next);
}
/*Add new entry to the end of the list*/
static inline void listAddTail(LIST_ListHead *item, LIST_ListHead *head) {
  listAddElement(item, head->prev, head);
}

/* delete item from list */
static inline void listDelete(LIST_ListHead *list) {
  list->next->prev = list->prev;
  list->prev->next = list->next;

  list->prev = NULL;
  list->next = NULL;
}

#endif
