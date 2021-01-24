#ifndef test_h
#define test_h

#define UNEXECUTED 0
#define PASS 1
#define FAIL -1

struct test_data{
    char *test_status;
    int total_tests;
} static test_data;

static int test_index = 0;
static const char *test_description = "";
static const char *test_label = "";
static const char *suite_label = "";


void test_printf(const char *format, ... );
int test_strcmp(const char * str1, const char * str2 );
int test_results(struct test_data tdata);
void test_runner(int run_location, int count);

#define TEST_RUN(TEST_DATA) test_index=-1; test_runner(0, 1); INIT_TESTING(TEST_DATA) test_index=-1; test_runner(0, 0);

#define TEST_RESULTS(TEST_DATA) test_results(TEST_DATA);

#define TEST_RUNNER void test_runner(int callback_id, int count)

#define TEST_SUITE(SUITE_LABEL) suite_label=SUITE_LABEL; switch(callback_id)

#define TEST_CASE(TEST_LABEL, DESCRIPTION) test_index++; test_label=TEST_LABEL; test_description=DESCRIPTION; if(!count)

#define TEST_ASSERT_EQUAL(EXPECTED, GOT) if (EXPECTED != GOT){ test_data.test_status[test_index] = FAIL; \
                                               test_printf( "FAILED: %s:%d %s.%s "  #EXPECTED " != " #GOT " %s\n",__FILE__ , __LINE__, suite_label, test_label, test_description); } \
                                         else { if(test_data.test_status[test_index] != FAIL) test_status[test_index] = PASS; \
                                               test_printf( "PASSED: %s:%d %s.%s\n",__FILE__ , __LINE__, suite_label, test_label); } 

#define TEST_ASSERT_EQUAL_EX(EXPECTED, GOT, CAST_TO, PRINT_TYPE) if ((CAST_TO)EXPECTED != (CAST_TO)GOT){ test_data.test_status[test_index] = FAIL; \
                                               test_printf( "FAILED: %s:%d %s.%s "  #EXPECTED " = " PRINT_TYPE " != " #GOT " = " PRINT_TYPE " %s\n",\
                                               __FILE__ , __LINE__, suite_label, test_label, (CAST_TO)EXPECTED, (CAST_TO)GOT, test_description); } \
                                         else { if(test_data.test_status[test_index] != FAIL) test_data.test_status[test_index] = PASS; \
                                               test_printf( "PASSED: %s:%d %s.%s\n",__FILE__ , __LINE__, suite_label, test_label); } 

#define TEST_ASSERT_EQUAL_INT(EXPECTED, GOT)  TEST_ASSERT_EQUAL_EX(EXPECTED, GOT, int, "%d")
#define TEST_ASSERT_EQUAL_CHAR(EXPECTED, GOT)  TEST_ASSERT_EQUAL_EX(EXPECTED, GOT, char, "'%c'")
#define TEST_ASSERT_EQUAL_FLOAT(EXPECTED, GOT)  TEST_ASSERT_EQUAL_EX(EXPECTED, GOT, float, "%f")

#define TEST_ASSERT_EQUAL_STR(EXPECTED, GOT)  if (test_strcmp(EXPECTED, GOT) != 0){ test_data.test_status[test_index] = FAIL; \
                                               test_printf( "FAILED: %s:%d %s.%s "  #EXPECTED " = \"%s\" != " #GOT " = \"%s\" %s\n",\
                                               __FILE__ , __LINE__, suite_label, test_label, EXPECTED, GOT, test_description); } \
                                         else { if(test_data.test_status[test_index] != FAIL) test_data.test_status[test_index] = PASS; \
                                               test_printf( "PASSED: %s:%d %s.%s\n",__FILE__ , __LINE__, suite_label, test_label); } 

#define INIT_TESTING(TEST_DATA) TEST_DATA.total_tests = test_index+1; char test_status_data[test_index+1]; for(int i = 0; i < test_index; i++) test_status_data[i]=0; TEST_DATA.test_status = test_status_data;

#define TEST_CALLBACK(X) X.test_callback_id = __LINE__; X.test_call_index = 0; case __LINE__: if (callback_id != 0)
#define TEST_CALLBACK_FIELDS int test_callback_id; int test_call_index; 
#define TEST_CALLBACK_RUN(X) test_runner(X.test_callback_id); X.test_call_index++;

#endif // test_h

