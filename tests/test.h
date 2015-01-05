#ifndef TEST_H
#define TEST_H

#include <stdio.h>

/**************************************
Test.h

This is a collection of macros designed to facilitate the most basic unit
testing.

To use, simply write some test code and use assertMsg to test it with a
condition (Eg. assertMsg(i == 0, "i does not equal 0")) . After the asserts in
any particular test, call report with the name of the test to view the
results. (Eg. report("I Value Test")).
**************************************/

// 0 if no errors have occured.
// Otherwise keeps track of the number of errors present in a test.
static int testSuccess = 0;

// Evaluates cond and prints msg upon failure.
#define assertMsg(cond, msg) if ((!cond)) { printf("Error: "); printf(msg); testSuccess++; printf("\n"); }

// Call this after each test (each collection of asserts). Outputs the number
// of errors present from the last call of report(), or success if no errors
// were recorded.
#define report(msg) if ((testSuccess == 0)) { \
                      printf("Pass: "); \
                    } else { \
                      printf("Fail (%d): ", testSuccess); \
                    } \
                    printf(msg); printf("\n\n"); \
                    testSuccess = 0;

#endif //TEST_H
