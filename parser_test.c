#define PARSER_IMPLEMENTATION
#include "parser.h"

#include <stdio.h>
#include <string.h>

int
main() {
    FILE *f = fopen("text.txt", "r");
    char string[1024];
    fgets(string, sizeof(string), f);

    char **words = parse_string(string, '"', '\\', '\n');

    for(size_t i = 0; i < array_len(words); i++) {
        printf("%s\n", words[i]);
    }

    array_destroy(words);
}
