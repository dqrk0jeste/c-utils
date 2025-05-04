// this is a dynamic array library. since c does not support templates macros are the second best thing. general usage
// would go something like this.
//
// ```c
// int *array;
// array_init(&array);
// array_push(&array, 1);
// array_push(&array, 3);
// array_insert(&array, 1, 2); // insert 2 at index 1
// // loop through elements, the first way
// for(size_t i = 0; i < array_len(array); i++) {
//     ...
// }
// // loop through elements, the second way
// for(int *ptr = array; i <= array_last(array); ptr++) {
//     ...
// }
// ```
//
// note that some functions take pointers to your variable, so it can be modified if an reallocating happens. keep in
// mind that that means that looping the second way isnt safe if you call any such functions inside. you shouldn't hold
// more than one reference to the array, or you should handle invalidation of other pointers yourself.
#pragma once

#include <stdlib.h>

// clang-format off
#ifndef ARRAY_INITIAL_CAP
#define ARRAY_INITIAL_CAP 16
#endif

#define array_len(arr) (*((size_t *)(arr) - 1))
#define array_cap(arr) (*((size_t *)(arr) - 2))

// get the pointer to the last element of the array. takes the array variable.
#define array_last(arr) (arr + array_len(arr) - 1)
// get the index of the element pointer or -1 if not in the array. takes the array variable.
#define array_index_of(arr, ptr) (((ptr) < (arr) || (ptr) > array_last(arr)) ? -1 : (ptr) - (arr))
// get the previous element in the array (one before `ptr`). takes the array variable.
#define array_prev(arr, ptr) ((ptr) == (arr) ? NULL : (ptr) - 1)
// get the next element in the array (one after `ptr`). takes the array variable.
#define array_next(arr, ptr) ((ptr) == (array_last(arr)) ? NULL : (ptr) + 1)

// internal
#define array_alloc_start(arr) ((size_t *)(arr) - 2)

// initialize the array. takes a pointer to the array variable.
#define array_init(arr) do {                                                                                     \
    *(arr) = (typeof(*(arr)))((size_t *)(malloc(2 * sizeof(size_t) + ARRAY_INITIAL_CAP * sizeof(**(arr)))) + 2); \
    array_len(*(arr)) = 0;                                                                                       \
    array_cap(*(arr)) = ARRAY_INITIAL_CAP;                                                                       \
} while(0)

// destroys the array. takes the array variable.
#define array_destroy(arr) do {   \
    free(array_alloc_start(arr)); \
} while(0)

// push the value to the end of array. takes a pointer to the array variable.
#define array_push(arr, el) do {                                                 \
    if(array_len(*(arr)) == array_cap(*(arr))) {                                 \
        array_cap(*(arr)) *= 2;                                                  \
        *(arr) = (typeof(*(arr)))((size_t *)(realloc(array_alloc_start(*(arr)),  \
                2 * sizeof(size_t) + array_cap(*(arr)) * sizeof(**(arr)))) + 2); \
    }                                                                            \
    (*(arr))[array_len(*(arr))] = (el);                                          \
    array_len(*(arr))++;                                                         \
} while(0)

// remove the value at index `idx`. takes a pointer to the array variable.
#define array_remove(arr, idx) do {                               \
    for(size_t __i = (idx); __i < array_len(*(arr)) - 1; __i++) { \
            (*(arr))[__i] = (*(arr))[__i + 1];                    \
    }                                                             \
    array_len(*(arr))--;                                          \
} while(0)

// remove the value pointed by `ptr`. takes a pointer to the array variable.
#define array_remove_by_ptr(arr, ptr) do {                                    \
    for(typeof(*(arr)) __ptr = (ptr); __ptr < array_last(*(arr)); __ptr++) {  \
        *__ptr = *(__ptr + 1);                                                \
    }                                                                         \
    array_len(*(arr))--;                                                      \
} while(0)

// insert the value at index `idx`. takes a pointer to the array variable.
#define array_insert(arr, idx, el) do {                                          \
    if(array_len(*(arr)) == array_cap(*(arr))) {                                 \
        array_cap(*(arr)) *= 2;                                                  \
        *(arr) = (typeof(*(arr)))((size_t *)(realloc(array_alloc_start(*(arr)),  \
                2 * sizeof(size_t) + array_cap(*(arr)) * sizeof(**(arr)))) + 2); \
    }                                                                            \
    for(ssize_t __i = array_len(*(arr)) - 1; __i >= (idx); __i--) {              \
        (*(arr))[__i + 1] = (*(arr))[__i];                                       \
    }                                                                            \
    (*(arr))[(idx)] = (el);                                                      \
    array_len(*(arr))++;                                                         \
} while(0)

// remove the value after the one pointed by `ptr`. takes a pointer to the array variable.
#define array_insert_after(arr, after, el) do {                                  \
    if(array_len(*(arr)) == array_cap(*(arr))) {                                 \
        array_cap(*(arr)) *= 2;                                                  \
        *(arr) = (typeof(*(arr)))((size_t *)(realloc(array_alloc_start(*(arr)),  \
                2 * sizeof(size_t) + array_cap(*(arr)) * sizeof(**(arr)))) + 2); \
    }                                                                            \
    for(typeof(*(arr)) __ptr = array_last(*(arr)); __ptr > (after); __ptr--) {   \
        *(__ptr + 1) = *__ptr;                                                   \
    }                                                                            \
    *(after + 1) = (el);                                                         \
    array_len(*(arr))++;                                                         \
} while(0)

// remove the value before the one pointed by `ptr`. takes a pointer to the array variable.
#define array_insert_before(arr, before, el) do {                                \
    if(array_len(*(arr)) == array_cap(*(arr))) {                                 \
        array_cap(*(arr)) *= 2;                                                  \
        *(arr) = (typeof(*(arr)))((size_t *)(realloc(array_alloc_start(*(arr)),  \
                2 * sizeof(size_t) + array_cap(*(arr)) * sizeof(**(arr)))) + 2); \
    }                                                                            \
    for(typeof(*(arr)) __ptr = array_last(*(arr)); __ptr >= (before); __ptr--) { \
        *(__ptr + 1) = *__ptr;                                                   \
    }                                                                            \
    *(before) = (el);                                                            \
    array_len(*(arr))++;                                                         \
} while(0)

// clang-format on
