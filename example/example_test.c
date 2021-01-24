#include "test.h"

enum test_cases {
    TEST_WRITE_HELLO_FOPEN_FAIL = 0,
    TEST_WRITE_HELLO_FOPEN_SUCCESS,
    TOTAL_TEST_CASES
};

typedef int FILE;

struct {
    FILE *returnv;
    const char * filename;
    const char * mode;

    TEST_CALLBACK_FIELDS
} fopen_callback; 


FILE *fopen (const char * filename, const char * mode)
{
    fopen_callback.filename = filename;
    fopen_callback.mode = mode;
    TEST_CALLBACK_RUN(fopen_callback);
    return fopen_callback.returnv;
}

struct {
    int returnv;
    const char * format;
    TEST_CALLBACK_FIELDS
} printf_callback; 


int printf ( const char * format)
{
    printf_callback.format = format;
    TEST_CALLBACK_RUN(printf_callback);
    return printf_callback.returnv;
}

struct {
    int returnv;
    FILE *fp;
    const char * format;
    TEST_CALLBACK_FIELDS
} fprintf_callback; 

int fprintf (FILE *fp, const char * format)
{
    fprintf_callback.fp = fp;
    fprintf_callback.format = format;
    TEST_CALLBACK_RUN(fprintf_callback);
    return fprintf_callback.returnv;
}

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

