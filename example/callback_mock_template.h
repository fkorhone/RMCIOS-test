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
 
    test_runner(TEST_CALLBACK_NAME.test_callback_id); 
    TEST_CALLBACK_NAME.test_call_index++;
    return TEST_CALLBACK_NAME.returnv;
}

#undef TEST_FUNC_NAME
#undef TEST_CALLBACK_NAME 
#undef TEST_FUNC_RETURN_TYPE
#undef TEST_FUNC_PARAMS

