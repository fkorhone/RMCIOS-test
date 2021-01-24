
typedef int FILE;
#define TEST_FUNC_NAME fopen
#define TEST_CALLBACK_NAME fopen_callback
#define TEST_FUNC_RETURN_TYPE FILE *
#define TEST_FUNC_PARAMS PARAM(const char *, filename) SEP\
                         PARAM(const char *, mode)
#include "test_callback_template.h"

#define TEST_FUNC_NAME printf
#define TEST_CALLBACK_NAME printf_callback
#define TEST_FUNC_RETURN_TYPE int
#define TEST_FUNC_PARAMS PARAM(const char *, format)
#include "test_callback_template.h"

#define TEST_FUNC_NAME fprintf
#define TEST_CALLBACK_NAME fprintf_callback
#define TEST_FUNC_RETURN_TYPE int
#define TEST_FUNC_PARAMS PARAM(FILE *, fp) SEP\
                         PARAM(const char *, format)
#include "test_callback_template.h"

