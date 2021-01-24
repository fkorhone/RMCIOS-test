/*
    Template header for creating stub callbacks.

Uses set of macros to as parameters filled in the template:

TEST_FUNC_NAME - Name of function to create a stub 
TEST_CALLBACK_NAME - Name of the callback parameter and state data structure
TEST_FUNC_RETURN_TYPE - Return type from the function
TEST_FUNC_PARAMS - Function parameters. Each parameter is specified with PARAM(TYPE, NAME) -macro..
                   Parameters need to be separated using SEP -macro

EXAMPLE:
Create callback stub for stdlib's function "fopen" which have a prototype:

FILE *fopen(const char * filename, const char * mode);

typedef int FILE;
#define TEST_FUNC_NAME fopen
#define TEST_CALLBACK_NAME fopen_callback
#define TEST_FUNC_RETURN_TYPE FILE *
#define TEST_FUNC_PARAMS PARAM(const char *, filename) SEP PARAM(const char *, mode)
#include "test_callback_template.h"

The generated stub can be used in test:

TEST_RUNNER
{
    TEST_SUITE("fopen")
    {
        TEST_CASE("fail", "")
        {
            TEST_CALLBACK(fopen_callback)
            {
                TEST_ASSERT_EQUAL_STR(fopen_callback.filename, "test.txt")
                TEST_ASSERT_EQUAL_STR(fopen_callback.mode, "w")
                fopen_callback.returnv = 0;
                return;
            }
            int returnv = fopen("test.txt", "w");
            TEST_ASSERT_EQUAL_INT(returnv, 1)
        }
    }
}

int main(void)
{
    TEST_RUN(test_data)
    return TEST_RESULTS(test_data)
}

*/

#undef SEP
#define SEP
#undef PARAM
#define PARAM(TYPE, NAME) TYPE NAME;

struct {
    TEST_FUNC_RETURN_TYPE returnv;
    TEST_FUNC_PARAMS
    int test_callback_id; 
    int test_call_index; 
} TEST_CALLBACK_NAME ; 

#undef SEP
#define SEP ,
#undef PARAM
#define PARAM(TYPE, NAME) TYPE NAME
TEST_FUNC_RETURN_TYPE TEST_FUNC_NAME ( TEST_FUNC_PARAMS )
{
#undef SEP
#define SEP
#undef PARAM
#define PARAM(TYPE, NAME) TEST_CALLBACK_NAME.NAME = NAME;
    TEST_FUNC_PARAMS
 
    test_runner(TEST_CALLBACK_NAME.test_callback_id, 0); 
    TEST_CALLBACK_NAME.test_call_index++;
    return TEST_CALLBACK_NAME.returnv;
}

#undef TEST_FUNC_NAME
#undef TEST_CALLBACK_NAME 
#undef TEST_FUNC_RETURN_TYPE
#undef TEST_FUNC_PARAMS

