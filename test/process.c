#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    pid_t pid;
    int i = 0;
    for (i; i < 3; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            break;
        }
    }
    if (pid > 0)
    {
        printf("parent pid %d running...\n", getpid());
        while (1)
        {
            sleep(1);
        }
    }
    else if (pid == 0)
    {
        printf("child pid %d , ppid %d i %d running...\n", getpid(), getppid(), i);
        while (1)
        {
            sleep(1);
        }
        
    }
    else
    {
        printf("error");
        return 1;
    }

    return 0;
}