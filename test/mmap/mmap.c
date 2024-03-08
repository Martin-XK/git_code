#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int* ptr = NULL;
    int fd, filesize;
    fd = open("map", O_RDWR);
    filesize = lseek(fd, 0, SEEK_END);
    if((ptr = mmap(NULL, 0, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        perror("mmap failed");
        exit(0);
    }
    close(fd);
    ptr[0] = 0x34333231;
    munmap(ptr, filesize);
    return 0;
}