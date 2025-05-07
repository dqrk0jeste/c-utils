#define STRING_IMPLEMENTATION
#include "string.h"

#include <time.h>

#include "test.h"

int
main() {
    PRINT_TEST_INFO;

    char *a = string_new("this is a string");
    ASSERT(string_len(a) == 16);
    ASSERT(string_cap(a) > 16);
    ASSERT(a[16] == 0);

    ASSERT(strcmp(a, "this is a string") == 0);

    char *a_cloned = string_clone(a);
    ASSERT(string_len(a_cloned) == 16);
    ASSERT(string_cap(a_cloned) > 16);
    ASSERT(a_cloned[16] == 0);

    ASSERT(string_equal(a, a_cloned));
    string_destroy(a_cloned);

    char *b = string_new_with_capacity("this is also a string", 50);
    ASSERT(string_len(b) == 21);
    ASSERT(string_cap(b) == 50);
    ASSERT(b[21] == 0);

    ASSERT(!string_equal(a, b));

    char *c = string_concat(a, b);
    ASSERT(string_len(c) == string_len(a) + string_len(b));
    ASSERT(c[string_len(a) + string_len(b)] == 0);

    ASSERT(string_index_of(a, 's', 0) == 3);
    ASSERT(string_index_of(a, 's', 4) == 6);
    ASSERT(string_index_of(a, 'A', 0) == -1);

    string_append(&a, '!');
    ASSERT(strcmp(a, "this is a string!") == 0);
    string_append_string(&a, b);
    ASSERT(string_len(a) == 38);
    ASSERT(strcmp(a, "this is a string!this is also a string") == 0);
    string_append(&a, '.');

    ASSERT(string_index_of_any(a, "!.", 0, NULL) == 16);
    char which;
    ASSERT(string_index_of_any(a, "!.", 18, &which) == 38);
    ASSERT(which == '.');

    string_destroy(a);
    string_destroy(b);
    string_destroy(c);

    // test bunch of them with sanitizers
    char *s = string_new_empty();
    srand(time(0));
    for(size_t i = 0; i < 10000; i++) {
        char c = rand() % 127 + 1;
        string_append(&s, c);
        string_append_c_string(&s, "blah");
    }

    char *to_append = string_new("append");
    for(size_t i = 0; i < 10000; i++) {
        string_append_string(&s, to_append);
    }

    string_destroy(s);
    string_destroy(to_append);

    PRINT_TEST_PASSED;
    return 0;
}
