#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define MSG "qwertyuiop"
int main()
{
    int fd = open("有名管道", O_RDONLY);
    char buffer[4096];
    read(fd, buffer, sizeof(buffer));
    printf("read process %d buffer %s\n", getpid(), buffer);
    close(fd);
    return 0;
}