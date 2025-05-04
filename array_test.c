#define ARRAY_INITIAL_CAP 2
#include "array.h"

#include <stdbool.h>
#include <stdint.h>

#include "test.h"

struct user {
    char *name;
    uint32_t age;
};

int
main() {
    PRINT_TEST_INFO;

    struct user *arr;
    array_init(&arr);

    array_push(&arr, ((struct user){"john", 25}));
    array_push(&arr, ((struct user){"tommy", 30}));
    array_push(&arr, ((struct user){"arthur", 32}));
    array_push(&arr, ((struct user){"ada", 27}));

    ASSERT(array_len(arr) == 4);
    ASSERT(array_last(arr)->age == 27);
    ASSERT(array_index_of(arr, &arr[2]) == 2);
    ASSERT(array_index_of(arr, &arr[45]) == -1);
    ASSERT(array_prev(arr, &arr[0]) == NULL);
    ASSERT(array_prev(arr, &arr[1])->age == 25);
    ASSERT(array_next(arr, &arr[3]) == NULL);
    ASSERT(array_next(arr, &arr[2])->age == 27);

    array_remove(&arr, 2);
    ASSERT(arr[2].age == 27);

    array_push(&arr, ((struct user){"esme", 19}));
    ASSERT(arr[array_len(arr) - 1].age == 19);

    array_insert(&arr, 1, ((struct user){"polly", 50}));
    ASSERT(arr[1].age == 50);

    array_insert(&arr, 0, ((struct user){"aberama", 56}));
    ASSERT(arr[0].age == 56);

    array_remove_by_ptr(&arr, &arr[2]);
    ASSERT(arr[2].age == 30);

    array_insert_after(&arr, &arr[3], ((struct user){"finn", 20}));
    ASSERT(arr[4].age == 20);

    array_insert_before(&arr, &arr[4], ((struct user){"micheal", 28}));
    ASSERT(arr[4].age == 28);

    printf("\nfinal array: len = %zu, cap = %zu\n", array_len(arr), array_cap(arr));
    for(size_t i = 0; i < array_len(arr); i++) {
        printf("    a[%zu] = { \"%s\", %u }\n", i, arr[i].name, arr[i].age);
    }

    array_destroy(arr);

    PRINT_TEST_PASSED;
    return 0;
}
