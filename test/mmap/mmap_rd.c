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
    ptr = mmap(NULL, sizeof(shared_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    while (1)
    {
        printf("%d %s\n", ptr->id, ptr->name);
        sleep(1);
    }
    close(fd);
    munmap(ptr, sizeof(shared_t));
    return 0;
}