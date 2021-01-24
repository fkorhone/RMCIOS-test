GCC?=gcc
TEST_DIR?=../
OUTPUT_NAME=example
TEST_NAME=test_example
SOURCES=example.c
TEST_SOURCES=example_test.c ../test.c
TEST_CFLAGS=-DTEST
TEST_CFLAGS+=-I${TEST_DIR}

program:
	$(GCC) ${SOURCES} -o ${OUTPUT_NAME}.exe

test: build_test
	${TEST_NAME}.exe

build_test:
	$(GCC) ${TEST_SOURCES} ${TEST_CFLAGS} -o ${TEST_NAME}.exe



