#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct
{
    int id;
    char name[1024];
}shared_t;

int main()
{
    shared_t* ptr = NULL;
    int fd;
    fd = open("Mmapfile", O_RDWR);
    ftruncate(fd, sizeof(shared_t));
    ptr = mmap(NULL, sizeof(shared_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ptr->id = 0;
    bzero(ptr->name, 1024);
    while (1)
    {
        ++(ptr->id);
        sprintf(ptr->name, "托马斯 %d", ptr->id);
        sleep(1);
    }
    close(fd);
    munmap(ptr, sizeof(shared_t));
    return 0;
}