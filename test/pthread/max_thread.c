#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* twk(void* arg)
{
    // 普通线程代码区
    while (1)
    {
        sleep(1);
    }
}

int main(void)
{
    // 主线程代码区
    pthread_t tid;
    int err;
    int flag = 0;
    while (1)
    {
        if ((err = pthread_create(&tid, NULL, twk, NULL)) > 0)
        {
            printf("thread_create failed:%s\n", strerror(err));
            exit(0);
        }
        printf("%d\n", ++flag);
    }
    return 0;
}
