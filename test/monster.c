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
        while ((zpid = wait(NULL)) > 0)
        {
            sleep(1);
            pid = fork();
            if (pid == 0)
            {
                goto tryagain;
            }
        }
    }
    else if (pid == 0)
    {
        tryagain:
            execl("/home/sonyokukin/test/hello", "hello", NULL);
    }
    else
    {
        perror("fork call failed");
        exit(0);
    }
    return 0;
}
