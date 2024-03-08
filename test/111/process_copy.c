#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int Pram_Check(const char* src, int argc, int pronum)
{
    if (access(src, F_OK) != 0)
    {
    if (pronum <= 5 || pronum >=100)
    {
        printf("pronum is error\n");
        return -1;
    }
    if (argc < 3)
    {
        printf("file is not exist\n");
        return -1;
    }
        printf("Pragama_num is error\n");
        return -1;
    }
}

int block_cur(const char* src, int pronum)
{
    int fd = open(src, O_RDONLY);
    if (-1 == fd)
    {
        printf("open file fail\n");
        return -1;
    }
    int fsize = lseek(fd, 0, SEEK_END);
    if (fsize % pronum == 0)
    {
        return fsize / pronum;
    }
    else
    {
        return fsize / pronum + 1;
    }
}

int Process_create(const char* src, const char* dest, int pronum, int blocksize)
{
    pid_t pid;
    int i = 0;
    for (i; i < pronum; i++)
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
                sleep(1);
            }
        }
    }
    else if (pid == 0)
    {
        int pos = i * blocksize;
        char str_blocksize[100];
        char str_pos[100];
        sprintf(str_blocksize, "%d", blocksize);
        sprintf(str_pos, "%d", pos);
        execl("/home/sonyokukin/test/111/copy", "copy", src, dest, str_blocksize, str_pos, NULL);
    }
    else
    {
        perror("fork call failed");
        exit(0);
    }
}

// 主函数
int main(int argc, char* argv[])
{
    int pronum;
    if(argv[3] == 0)
    {
        pronum = 5;
    }
    else
    {
        pronum = atoi(argv[3]);
    }

    if (-1 == Pram_Check(argv[1], argc, atoi(argv[3])))
    {
        return -1;
    }

    int blocksize = block_cur(argv[1], atoi(argv[3]));
    if (-1 == blocksize)
    {
        return -1;
    }
    else
    {
        // 创建线程
        Process_create(argv[1], argv[2], atoi(argv[3]), blocksize);
    }
    

    return 0;
}