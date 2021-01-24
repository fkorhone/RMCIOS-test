#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "test.h" 

void test_printf(const char *format, ... )
{
    va_list args;
    va_start (args, format);
    vprintf(format, args);
    va_end(args);
}

int test_strcmp(const char * str1, const char * str2 )
{
    return strcmp(str1, str2);
}

int test_results(struct test_data tdata)
{
    // Result summary:
    int passed = 0;
    int failed = 0;
    int unexecuted = 0;
    int i;
    for (i = 0; i < tdata.total_tests; i++)
    {
        if (tdata.test_status[i] == PASS)
        {
            passed++;
        }
        if (tdata.test_status[i] == FAIL)
        {
            failed++;
        }
        if (tdata.test_status[i] == UNEXECUTED)
        {
            unexecuted++;
        }
    }
    test_printf("\npassed:%d failed:%d unexecuted:%d total:%d\n", passed, failed, unexecuted, tdata.total_tests);
    if (failed > 0 || unexecuted > 0) return EXIT_FAILURE;
    else return EXIT_SUCCESS ;
}

