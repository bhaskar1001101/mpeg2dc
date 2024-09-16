#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

#define TEST(name) void test_##name()
#define RUN_TEST(name) do { \
    printf("Running %s...\n", #name); \
    test_##name(); \
} while (0)

#define ASSERT(condition, message) do { \
    if (!(condition)) { \
        printf("%sFAILED: %s\n%s", KRED, message, KNRM); \
        exit(1); \
    } \
} while (0)

#define ASSERT_EQUAL(expected, actual, message) do { \
    if ((expected) != (actual)) { \
        printf("%sFAILED: %s\nExpected: %d, Actual: %d\n%s", KRED, message, (expected), (actual), KNRM); \
        exit(1); \
    } \
} while (0)

#define ASSERT_STRING_EQUAL(expected, actual, message) do { \
    if (strcmp((expected), (actual)) != 0) { \
        printf("%sFAILED: %s\nExpected: %s, Actual: %s\n%s", KRED, message, (expected), (actual), KNRM); \
        exit(1); \
    } \
} while (0)

#endif // TEST_HARNESS_H