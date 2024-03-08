#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define MSG "qwertyuiop"
int main()
{
    int fd = open("有名管道", O_WRONLY);
    printf("aa\n");
    write(fd, MSG, strlen(MSG));
    printf("write process success..\n");
    close(fd);
    return 0;
}