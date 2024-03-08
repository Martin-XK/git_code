#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid > 0)
    {
        pid_t zpid;
        printf("parent pid %d running..\n", getppid());
        zpid = wait(NULL);
        printf("parent wait zombie success, zpid %d\n", zpid);
    }
    else if (pid == 0)
    {
        printf("a");
        printf("b");
        execl("/user/bin/firefox", "firefox", NULL);
        printf("c");
        exit(0);
    }
    return 0;
}