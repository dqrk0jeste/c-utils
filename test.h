// minimal testing utils
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr)                                           \
    do {                                                       \
        printf("ASSERTION `" #expr "` on line %d ", __LINE__); \
        if(expr) {                                             \
            printf("PASSED\n");                                \
        } else {                                               \
            printf("FAILED\n");                                \
            exit(1);                                           \
        }                                                      \
    } while(0)

#define PRINT_TEST_INFO printf("--TESTING %s--\n", __FUNCTION__)
#define PRINT_TEST_PASSED printf("--TEST %s PASSED--\n", __FUNCTION__)
