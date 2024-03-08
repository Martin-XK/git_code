#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int blocksize = atoi(argv[3]);
    int pos = atoi(argv[4]);
    char buffer[blocksize];
    printf("success\n");
    int sfd = open("/home/sonyokukin/test/111/1.jpg", O_RDONLY);
    int dfd = open("/home/sonyokukin/test/111/2.jpg", O_RDWR|O_CREAT, 0664);
    lseek(sfd, pos, SEEK_SET);
    lseek(dfd, pos, SEEK_SET);
    int len = read(sfd, buffer, sizeof(buffer));
    write(dfd, buffer, len);
    
    close(sfd);
    close(dfd);

    return 0;
}