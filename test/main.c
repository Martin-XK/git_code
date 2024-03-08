#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <signal.h>
#include <regex.h>
#include <sys/mman.h>

int main()
{
    int reg_num = 2;
    const char* reg_str = "<name>\\([^<]\\+\\?\\)</name>";
    regex_t reg;
    regmatch_t Ma[2];

    regcomp(&reg, reg_str, 0);

    char* map_str = NULL;
    char* jptr;
    int fsize;
    int fd;
    fd = open("test", O_RDWR);
    fsize = lseek(fd, 0, SEEK_END);
    map_str = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
    // printf("%s\n",map_str);
    jptr = map_str;

    char result[100];
    while ((regexec(&reg, map_str, reg_num, Ma, 0)) == 0)
    {
        bzero(result, sizeof(result));
        snprintf(result, Ma[1].rm_eo - Ma[1].rm_so + 1, "%s", map_str + Ma[1].rm_so);
        printf("%s\n", result);
        map_str += Ma[0].rm_eo;
    }
    
    munmap(jptr, fsize);
    regfree(&reg);
    close(fd);

    return 0;
}
