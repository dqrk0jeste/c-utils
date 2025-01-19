#include "array.h"
#include "test.h"

#include <stdint.h>
#include <stdbool.h>

struct user {
  char *name; 
  uint32_t age;
};

int main() {
  PRINT_TEST_INFO;
  struct user *arr;

  array_init(&arr);

  array_push(&arr, ((struct user){ "john", 25 }));
  array_push(&arr, ((struct user){ "tommy", 30 }));
  array_push(&arr, ((struct user){ "arthur", 32 }));
  array_push(&arr, ((struct user){ "ada", 27 }));

  array_remove(&arr, 2);
  ASSERT(arr[2].age == 27);

  array_push(&arr, ((struct user){ "esme", 19 }));
  ASSERT(arr[array_len(arr) - 1].age == 19);

  array_insert(&arr, 1, ((struct user){ "polly", 50 }));
  ASSERT(arr[1].age == 50);

  array_remove(&arr, 2);
  ASSERT(arr[2].age == 27);

  /*printf("\nfinal array \nlen: %zu, cap: %zu\n", array_len(arr), array_cap(arr));*/
  /**/
  /*for(size_t i = 0; i < array_len(arr); i++) {*/
  /*  printf("a[%zu] = { \"%s\", %u }\n", i, arr[i].name, arr[i].age);*/
  /*}*/

  array_destroy(&arr);

  PRINT_TEST_PASSED;
  return 0;
}
