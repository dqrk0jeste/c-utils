/* minimal testing library */
#include <stdlib.h>
#include <stdio.h>

#define ASSERT(expr) { \
  printf("ASSERTION `" #expr "` at line %d ", __LINE__); \
  if(expr) { \
    printf("PASSED\n"); \
  } else { \
    printf("FAILED\n"); \
    exit(1); \
  } \
}

#define PRINT_TEST_INFO printf("--TESTING %s--\n", __FUNCTION__)
#define PRINT_TEST_PASSED printf("--TEST %s PASSED--\n", __FUNCTION__)
