#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    pid_t pid;
    int i;
    for (i = 0; i < 5; i++)
    {
        pid = fork();
        if (pid == 0)
            break;
    }
    if (pid > 0)
    {
        printf("parent pid %d\n", getpid());
        pid_t zpid;
        while ((zpid = waitpid(-1, NULL, WNOHANG)) != -1)
        {
            if (zpid > 0)
            {
                printf("parent wait child success, zpid %d\n", zpid);
            }
            else
            {
                printf("waitpid tryagain, parent exec...\n");
                usleep(500000);
            }
        }
    }
    else if (pid == 0)
    {
        printf("child pid %d\n", getpid());
        sleep(i);
        exit(i);
    }
    else
    {
        perror("fork call failed");
        exit(0);
    }
    return 0;
}