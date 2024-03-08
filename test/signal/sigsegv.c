#include <stdio.h>

void err(void)
{
    char * str = "message";
    printf("running code 07...\n");
    printf("running code 08...\n");
    str[0] = 'M';
    printf("running code 09...\n");
}

int main(void)
{
    printf("running code 01...\n");
    printf("running code 02...\n");
    printf("running code 03...\n");
    printf("running code 04...\n");
    printf("running code 05...\n");
    err();
    printf("running code 06...\n");
    return 0;
}