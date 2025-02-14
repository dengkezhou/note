/******************************************************************************
 * Copyright (C) 2013-2018 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 *
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * test_harness_log.h
 * Common helper functions for tests.
 ******************************************************************************
 */

#ifndef TEST_HARNESS_LOG_H
#define TEST_HARNESS_LOG_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// LEGACY_FUNC_TESTING - deprecated, for people who use
// - fc_analyse_test_logs.sh
// - mipi_analyse_test_logs.sh
// if someone uses analyse_test_logs.sh please let me know
// The idea is to use the analyse_mech_test_logs.sh for functional tests too (like Alan does)
// so that we have only one file that analyses and returns (true or false) result for Jenkins

// keywords used when printing results for each test separatelty
#ifdef LEGACY_FUNC_TESTING
 // additional (PASSED) is provided to unify output from the test report generator (repgen.py)
 #define TEST_KEYWORD_PASSED    "Test Completed (PASSED)"
 #define TEST_KEYWORD_FAILED    "Test Failed (FAILED)"
#else
 #define TEST_KEYWORD_PASSED    "PASSED"
 #define TEST_KEYWORD_FAILED    "FAILED"
#endif
#define TEST_KEYWORD_SKIPPED    "SKIPPED"
#define TEST_KEYWORD_NOTSUP     "NOT SUPPORTED"
#define TEST_KEYWORD_SIMTOUT    "SIMULATION TIMEOUT"

// keywords used when printing summary
#define TEST_KEYWORD_SUMMARY_CALLS      "calls"
#define TEST_KEYWORD_SUMMARY_PASSED     "passed"
#define TEST_KEYWORD_SUMMARY_FAILED     "failed"
#define TEST_KEYWORD_SUMMARY_NOTSUP     "not supported"
#define TEST_KEYWORD_SUMMARY_SKIPPED    "skipped"
#define TEST_KEYWORD_SUMMARY_SIMTOUT    "simulation timout"

// others
#define TEST_KEYWORD_RUNNING_TEST  "running test"

// must be called before 1st test function (TESTING_SUMMARY)
#define START_TESTING(testData) do {\
    testData.calls = 0;\
    testData.passed = 0;\
    testData.failed = 0;\
    testData.notsup = 0;\
    testData.skipped = 0;\
    printf("\nTESTING: RUNNING: %u:%s\n", testData.groupIndex, testData.groupName);\
  } while (0)

// internal macro prints result for a test, user must not call it directly
#define TESTING_TEST_BASE(testName, testData, result) do {\
    testData.calls++;\
    printf("\nTESTING: %s: %s ", testData.groupName, testName);\
    printf("%s\n", result);\
  } while (0)

// this macro is only for compatibility when not using analyse_mech_test_logs.sh
// should be called before: TESTING_TEST_PASSED, TESTING_TEST_FAILED etc.
#define TESTING_RUNNING_TEST(testData)\
  printf("\n%s %u\n", TEST_KEYWORD_RUNNING_TEST, testData.calls + 1)

// (optional) output produced by this macro is not interpreted by tests anlysing tools
// but provide useful information about currently testing function
// should  be called before running a single test
#define TESTING_RUNNING_TEST_EX(testName, testData, testNumber, testNumberTotal)\
  printf("\n%s %u/%u %s:%s\n", TEST_KEYWORD_RUNNING_TEST, testNumber, testNumberTotal, testData.groupName, testName)

// use it when function passed
// generates line as follow:
// TESTING: functional: testfuncPassed PASSED
#define TESTING_TEST_PASSED(testName, testData) do {\
    testData.passed++;\
    TESTING_TEST_BASE(testName, testData, TEST_KEYWORD_PASSED);\
  } while (0)

// use it when function failed
// generates line as follow:
// TESTING: functional: testfuncFailed FAILED
#define TESTING_TEST_FAILED(testName, testData) do {\
    testData.failed++;\
    TESTING_TEST_BASE(testName, testData, TEST_KEYWORD_FAILED);\
  } while (0)

// use it when function is not supported
// generates line as follow:
// TESTING: functional: testfuncNotSup NOT SUPPORTED
#define TESTING_TEST_NOTSUP(testName, testData) do {\
    testData.notsup++;\
    TESTING_TEST_BASE(testName, testData,TEST_KEYWORD_NOTSUP);\
  } while (0)

// use it when a test for a function is skipped
// generates line as follow:
// TESTING: functional: testfuncSkipped SKIPPED
#define TESTING_TEST_SKIPPED(testName, testData) do {\
    testData.skipped++;\
    TESTING_TEST_BASE(testName, testData,TEST_KEYWORD_SKIPPED);\
  } while (0)

// prints summary for all tests called after START_TESTING
// TESTING: --------------------------------------
// TESTING: SUMMARY:
// TESTING: functional: 15 calls, 15 passed
// TESTING: --------------------------------------
// TESTING: FINISHED: 0:functional
#define TESTING_SUMMARY(testData) do {\
    printf("\nTESTING: -------------------------------------------\n");\
    printf("TESTING: SUMMARY:\n");\
    printf("TESTING: %s: ", testData.groupName);\
    printf("%u %s", testData.calls, TEST_KEYWORD_SUMMARY_CALLS);\
    printf(", %u %s", testData.passed, TEST_KEYWORD_SUMMARY_PASSED);\
    if (testData.failed) printf(", %u %s", testData.failed, TEST_KEYWORD_SUMMARY_FAILED);\
    if (testData.notsup) printf(", %u %s", testData.notsup, TEST_KEYWORD_SUMMARY_NOTSUP);\
    if (testData.skipped) printf(", %u %s", testData.skipped, TEST_KEYWORD_SUMMARY_SKIPPED);\
    printf("\nTESTING: -------------------------------------------\n");\
    printf("TESTING: FINISHED: %u:%s\n", testData.groupIndex, testData.groupName);\
 } while (0)

// structure keeping general test information and results/statistics
typedef struct {
    unsigned int calls; // counter for  executed tests
    unsigned int passed; // counter for passed tests
    unsigned int failed; // counter for failed tests
    unsigned int notsup; // counter for not supported tests
    unsigned int skipped; // counter for skipped tests
    char* groupName; // name for a group of tests e.g.: mechanical, functional, accessReg, testHotPlug
    unsigned int groupIndex; // index for a group of tests
} TestData;

/*-------------------EXAMPLE----------------*/

#if 0

TestData testData;

// function with test passes
void testfuncPassed() {
    // testing code...
    TESTING_TEST_PASSED("testfuncPassed", testData);
}

// function with a test that failes
void testfuncFailed() {
    // testing code...
    TESTING_TEST_FAILED("testfuncFailed", testData);
}

// function with test that is not supported
void testfuncNotSup() {
    // testting code...
    TESTING_TEST_NOTSUP("testfuncNotSup", testData);
}

// function with a skipped test
void testfuncSkipped() {
    // testing code...
     TESTING_TEST_SKIPPED("testfuncSkipped", testData);
}

void runAllTests()
{
    char * testGroupName = "functional";
    testData.groupName = testGroupName;
    testData.groupIndex = 0;

    START_TESTING(testData);
    testfuncPassed();
    testfuncNotSup();
    testfuncFailed();
    testfuncSkipped();
    TESTING_SUMMARY(testData); // must be called when all functions are tested
}

int main(void)
{
    runAllTests();
    return 0;
}
#endif

#endif // TEST_HARNESS_LOG_H
