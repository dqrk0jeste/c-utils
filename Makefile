CFLAGS=-g -fsanitize=address,undefined

all: build/array_test build/list_test
	build/array_test
	build/list_test
	build/string_test

build/array_test: array_test.c array.h build
	$(CC) $< $(CFLAGS) -o $@

build/list_test: list_test.c list.h build
	$(CC) $< $(CFLAGS) -o $@

build/string_test: string_test.c string.h build
	$(CC) $< $(CFLAGS) -o $@

build/parser_test: parser_test.c parser.h build
	$(CC) $< $(CFLAGS) -o $@

test_array: build/array_test
	$<

test_list: build/list_test
	$<

test_string: build/string_test
	$<

test_parser: build/parser_test
	$<

build:
	mkdir build

clean:
	rm -rf build 2>/dev/null

.PHONY: clean array_test list_test string_test
