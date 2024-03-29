# RMCIOS-test
Testing framework/abstraction layer

## Test Callback Template
test_callbach_template.h

Uses set of macros to as parameters filled in the template. 
Creates a stub function that assigns parameters to a structure and calls test runner. Gives callback location (case id) to the test runner. Test runner will jump to the callback case and access parameters from the callback structure. 

Macros used in the template header:
* TEST_FUNC_NAME - Name of function to create a stub 
* TEST_CALLBACK_NAME - Name of the callback parameter and state data structure
* TEST_FUNC_RETURN_TYPE - Return type from the function. Undef for "void" return types.
* TEST_FUNC_PARAMS - Function parameters. Each parameter is specified with PARAM(TYPE, NAME) -macro.
                   Parameters need to be separated using SEP -macro

## Example

### Code to test
```
// code_to_test.c

int write_hello(void)
{
    FILE *fp;
    fp = fopen("test.txt", "w");
    if(!fp)
    {
        printf("Could not open file test.txt\n");
        return 1;
    }
    else
    {
        printf("File opened succesfully, writing to file test.txt\n");
        fprintf(fp, "Hello world!\n");
        return 0;
    }
}
```

### Callback stubs for used functions.
```
// stdio_stubs.h

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
```

### Test code
```
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
```

