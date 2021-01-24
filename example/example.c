#ifndef TEST
#include <stdio.h>
#endif

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

#ifndef TEST
int main(void)
{
    return write_hello();
}
#endif

