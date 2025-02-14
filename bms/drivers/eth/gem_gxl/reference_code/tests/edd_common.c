/**********************************************************************
 * Copyright (C) 2018-2019 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 **********************************************************************/
#include "edd_common.h"

CEDI_Drv_TestData d;
static char groupName[1024];
static char notSupReason[1024];
/* global string used to format error message */
char errMsg[1024];
int passed = TEST_SUCCESS; /* any validate__ fail will clear this */

void start_test(char *name) {
    // reset 'passed' to default value
    passed = TEST_SUCCESS;
    d.name = name;
}

void test_pass() {
    TESTING_TEST_PASSED(d.name, d.td);
}

void test_fail() {
    TESTING_TEST_FAILED(d.name, d.td);
}

void test_init(char *group) {
    memset(&d.td, 0, sizeof(TestData));
    // set group name and clear not supported reason
    snprintf(groupName, sizeof(groupName), "%s", group);
    snprintf(notSupReason, sizeof(notSupReason), "%s", "");
    d.td.groupName = groupName;
    d.notSupReason = notSupReason;
    START_TESTING(d.td);
}

/* Set the not supported reason into globally accessible table. Set the passed status to TEST_NOTSUP.
 * Provides info about a test result to end_test(). */
void set_not_supported_reason(char *reason) {
    snprintf(notSupReason, sizeof(notSupReason), "%s\n", reason);
    passed = TEST_NOTSUP;
}

void test_notsup() {
    TESTING_TEST_NOTSUP(d.name, d.td);
    // reason should be ready in notSupReason[1024], example of setting it:
    // it can be set by calling set_not_supported_reason(char *reason)
    printf("TESTING: COMMENT: %s: \n", d.notSupReason);
}

int end_test() {
    switch (passed) {
        case TEST_SUCCESS:
            test_pass();
            TESTING_SUMMARY(d.td);
            csp_test_complete(0);
            break;
            return 0;
        case TEST_NOTSUP:
            test_notsup();
            TESTING_SUMMARY(d.td);
            csp_test_complete(0);
            break;
            return 0;
        case TEST_FAILED:
        default:
            test_fail();
            TESTING_SUMMARY(d.td);
            csp_test_complete(1);
            break;
            return 1;
    }
    //only for avoid compiler warning
    return 0;
}
