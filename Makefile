CFLAGS="-fsanitize=address,undefined"

all: build/array_test build/list_test
	build/array_test
	build/list_test

build/array_test: array_test.c build
	$(CC) $< $(CFLAGS) -o $@

build/list_test: list_test.c build
	$(CC) $< $(CFLAGS) -o $@

test_array: build/array_test
	$<

build:
	mkdir build

clean:
	rm -rf build 2>/dev/null

.PHONY: clean array_test
