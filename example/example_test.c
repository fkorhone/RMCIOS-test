#include "test.h"

enum test_cases {
    TEST_WRITE_HELLO_FOPEN_FAIL = 0,
    TEST_WRITE_HELLO_FOPEN_SUCCESS,
    TOTAL_TEST_CASES
};

typedef int FILE;

#define TEST_CALLBACK_FIELDS int test_callback_id; int test_call_index; 
#define TEST_CALLBACK_RUN(X) test_runner(X.test_callback_id); X.test_call_index++;

#define TEST_FUNC_NAME fopen
#define TEST_CALLBACK_NAME fopen_callback
#define TEST_FUNC_RETURN_TYPE FILE *
#define TEST_FUNC_PARAMS PARAM(const char *, filename) SEP\
                         PARAM(const char *, mode)
#include "callback_mock_template.h"

#define TEST_FUNC_NAME printf
#define TEST_CALLBACK_NAME printf_callback
#define TEST_FUNC_RETURN_TYPE int
#define TEST_FUNC_PARAMS PARAM(const char *, format)
#include "callback_mock_template.h"

#define TEST_FUNC_NAME fprintf
#define TEST_CALLBACK_NAME fprintf_callback
#define TEST_FUNC_RETURN_TYPE int
#define TEST_FUNC_PARAMS PARAM(FILE *, fp) SEP\
                         PARAM(const char *, format)
#include "callback_mock_template.h"

#include "example.c"

void test_runner(int callback_id)
{
    switch(callback_id)
    {
        default:

        TEST_CASE(TEST_WRITE_HELLO_FOPEN_FAIL, "")
        {
            TEST_CALLBACK(fopen_callback)
            {
                TEST_ASSERT_EQUAL_STR(fopen_callback.filename, "test.txt")
                TEST_ASSERT_EQUAL_STR(fopen_callback.mode, "w")
                fopen_callback.returnv = 0;
                return;
            }
            TEST_CALLBACK(printf_callback)
            {
                TEST_ASSERT_EQUAL_STR(printf_callback.format, "Could not open file test.txt\n")
                return;
            }
            int returnv = write_hello();
            TEST_ASSERT_EQUAL_INT(returnv, 1)
        }
        
        TEST_CASE(TEST_WRITE_HELLO_FOPEN_SUCCESS, "")
        {
            TEST_CALLBACK(fopen_callback)
            {
                TEST_ASSERT_EQUAL_STR(fopen_callback.filename, "test.txt")
                TEST_ASSERT_EQUAL_STR(fopen_callback.mode, "w")
                fopen_callback.returnv = 56;
                return;
            }
            TEST_CALLBACK(printf_callback)
            {
                TEST_ASSERT_EQUAL_STR(printf_callback.format, "File opened succesfully, writing to file test.txt\n")
                return;
            }
            TEST_CALLBACK(fprintf_callback)
            {
                TEST_ASSERT_EQUAL_INT(fprintf_callback.fp, 56)
                TEST_ASSERT_EQUAL_STR(fprintf_callback.format, "Hello world!\n")
                return;
            }
            int returnv = write_hello();
            TEST_ASSERT_EQUAL_INT(returnv, 0)
        }
    }
}

int main(void)
{
    INIT_TESTING(test_data, TOTAL_TEST_CASES)
    test_runner(0);
    return test_results(test_data);
}

