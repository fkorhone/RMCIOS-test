#include "test.h"
#include "stdio_stub.h"
#include "example.c"

TEST_RUNNER
{
    TEST_SUITE("TEST_WRITE_HELLO")
    {   
        default:

        TEST_CASE("FOPEN_FAIL", "")
        {
            TEST_CALLBACK(fopen_callback)
            {
                TEST_ASSERT_EQUAL_STR(fopen_callback.filename, "test.txt")
                TEST_ASSERT_EQUAL_STR(fopen_callback.mode, "w")
                fopen_callback.return_value = 0;
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
        
        TEST_CASE("FOPEN_SUCCESS", "")
        {
            TEST_CALLBACK(fopen_callback)
            {
                TEST_ASSERT_EQUAL_STR(fopen_callback.filename, "test.txt")
                TEST_ASSERT_EQUAL_STR(fopen_callback.mode, "w")
                fopen_callback.return_value = 56;
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
    TEST_RUN(test_data)
    return TEST_RESULTS(test_data)
}

