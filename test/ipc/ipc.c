#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define MSG "hihihi"

int main()
{
    pid_t pid;
    int fds[2];
    pipe(fds);
    pid = fork();
    if (pid > 0)
    {
        close(fds[0]);
        write(fds[1], MSG, strlen(MSG));
        printf("parent %d write msg success\n", getpid());
        close(fds[1]);
        wait(NULL);
    }
    else if (pid == 0)
    {
        close(fds[1]);
        char buffer[1024];
        bzero(buffer, sizeof(buffer));
        read(fds[0], buffer, sizeof(buffer));
        printf("child read msg: %s\n", buffer);
        close(fds[0]);
        exit(0);
    }
    else
    {
        perror("fork call failed");
        exit(0);
    }
    return 0;
}
