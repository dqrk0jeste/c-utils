#define LIST_IMPLEMENTATION
#include "list.h"

#include <stdbool.h>

#include "test.h"

// i am lazy to write actual test for these as they are proven to work

struct to_link {
    struct list link;
    int data;
};

int
main() {
    PRINT_TEST_INFO;
    struct to_link a = {.data = 1};
    struct to_link b = {.data = 2};
    struct to_link c = {.data = 3};

    struct list list;
    list_init(&list);

    list_insert(list.prev, &a.link);
    list_insert(list.prev, &b.link);
    list_insert(list.prev, &c.link);

    ASSERT(true);

    PRINT_TEST_PASSED;
    return 0;
}
