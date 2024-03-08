#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* twk(void* arg)
{
    printf("pthread tid = 0x%x\n", (unsigned int)pthread_self());
}

int main(void)
{
    // 主线程代码区
    pthread_t tid;
    int err;
    int flag = 0;

    printf("Master tid = 0x%x\n", (unsigned int)pthread_self());

    if ((err = pthread_create(&tid, NULL, twk, NULL)) > 0)
    {
        printf("thread_create failed:%s\n", strerror(err));
        exit(0);
    }
    sleep(0);
    printf("Master create thread tid = 0x%x\n", (unsigned int)tid);
    return 0;
}
