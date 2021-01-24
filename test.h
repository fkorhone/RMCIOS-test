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
static int do_test=0;
static int test_case=-1;
static int test_stage=0;


void test_printf(const char *format, ... );
int test_strcmp(const char * str1, const char * str2 );
int test_results(struct test_data tdata);
void test_runner(int run_location);

#define TEST_CASE(TEST_ENUM, DESCRIPTION) test_index=TEST_ENUM;test_label=#TEST_ENUM; test_description=DESCRIPTION;\


#define TEST_ASSERT_EQUAL(EXPECTED, GOT) if (EXPECTED != GOT){ test_data.test_status[test_index] = FAIL; \
                                               test_printf( "FAILED: %s:%d %s "  #EXPECTED " != " #GOT " %s\n",__FILE__ , __LINE__, test_label, test_description); } \
                                         else { if(test_data.test_status[test_index] != FAIL) test_status[test_index] = PASS; \
                                               test_printf( "PASSED: %s:%d %s\n",__FILE__ , __LINE__, test_label); } 

#define TEST_ASSERT_EQUAL_EX(EXPECTED, GOT, CAST_TO, PRINT_TYPE) if ((CAST_TO)EXPECTED != (CAST_TO)GOT){ test_data.test_status[test_index] = FAIL; \
                                               test_printf( "FAILED: %s:%d %s "  #EXPECTED " = " PRINT_TYPE " != " #GOT " = " PRINT_TYPE " %s\n",\
                                               __FILE__ , __LINE__, test_label, (CAST_TO)EXPECTED, (CAST_TO)GOT, test_description); } \
                                         else { if(test_data.test_status[test_index] != FAIL) test_data.test_status[test_index] = PASS; \
                                               test_printf( "PASSED: %s:%d %s\n",__FILE__ , __LINE__, test_label); } 

#define TEST_ASSERT_EQUAL_INT(EXPECTED, GOT)  TEST_ASSERT_EQUAL_EX(EXPECTED, GOT, int, "%d")
#define TEST_ASSERT_EQUAL_CHAR(EXPECTED, GOT)  TEST_ASSERT_EQUAL_EX(EXPECTED, GOT, char, "'%c'")
#define TEST_ASSERT_EQUAL_FLOAT(EXPECTED, GOT)  TEST_ASSERT_EQUAL_EX(EXPECTED, GOT, float, "%f")

#define TEST_ASSERT_EQUAL_STR(EXPECTED, GOT)  if (test_strcmp(EXPECTED, GOT) != 0){ test_data.test_status[test_index] = FAIL; \
                                               test_printf( "FAILED: %s:%d %s "  #EXPECTED " = \"%s\" != " #GOT " = \"%s\" %s\n",\
                                               __FILE__ , __LINE__, test_label, EXPECTED, GOT, test_description); } \
                                         else { if(test_data.test_status[test_index] != FAIL) test_data.test_status[test_index] = PASS; \
                                               test_printf( "PASSED: %s:%d %s\n",__FILE__ , __LINE__, test_label); } 

#define INIT_TESTING(TEST_DATA, TEST_CASES) TEST_DATA.total_tests = TEST_CASES; char test_status_data[TEST_CASES] = {0}; TEST_DATA.test_status = test_status_data;

#define TEST_CALLBACK(X) X.test_callback_id = __LINE__; X.test_call_index = 0; case __LINE__: if (callback_id != 0)
#define TEST_CALLBACK_FIELDS int test_callback_id; int test_call_index; 
#define TEST_CALLBACK_RUN(X) test_runner(X.test_callback_id); X.test_call_index++;


#endif // test_h

