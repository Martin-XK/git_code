#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int daemon_jobs()
{
    int fd;
    time_t tp;
    char tbuf[1024];
    bzero(tbuf, sizeof(tbuf));
    if ((fd = open("time.log", O_RDWR|O_CREAT, 0664)) == -1)
    {
        perror("open call failed");
        exit(0);
    }
    while (1)
    {
        tp = time(NULL);
        ctime_r(&tp, tbuf);
        write(fd, tbuf, strlen(tbuf));
        bzero(tbuf, sizeof(tbuf));
        sleep(3);
    }
    close(fd);
    return 0;
}

void daemon_create()
{
    pid_t pid;
    pid = fork();
    if (pid > 0)
    {
        exit(0);
    }
    else if (pid == 0)
    {
        int errfd;
        setsid();
        errfd = open("error.log", O_RDWR | O_CREAT, 0664);
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(errfd, STDERR_FILENO);
        umask(0002);
        chdir("./");
        daemon_jobs();
    }
    else
    {
        perror("fork call failed");
    }
}

int main()
{
    daemon_create();
    return 0;
}