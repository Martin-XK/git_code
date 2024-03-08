#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    if (pid > 0)
    {
        pid_t zpid;
        printf("parent pid %d running..\n", getppid());
        sleep(10);
        zpid = wait(NULL);
        printf("parent wait zombie success, zpid %d\n", zpid);
    }
    else if (pid == 0)
    {
        printf("child pid %d ppid %d running..\n", getpid(), getppid());
        sleep(5);
        exit(0);
    }
    else
    {
        perror("fork failed");
        exit(0);
    }
    while (1)
    {
        sleep(1);
    }
 
    return 0;
}