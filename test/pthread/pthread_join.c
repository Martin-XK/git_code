#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* twk(void* arg)
{
    printf("pthread tid = 0x%x\n", (unsigned int)pthread_self());
    return (void*)0;
}

int main(void)
{
    // 主线程代码区
    pthread_t tid;
    int err;
    void* reval;

    printf("Master tid = 0x%x\n", (unsigned int)pthread_self());

    if ((err = pthread_create(&tid, NULL, twk, NULL)) > 0)
    {
        printf("thread_create failed:%s\n", strerror(err));
        exit(0);
    }
    if ((err = pthread_join(tid, &reval)) > 0)
    {
        printf("thread_create failed:%s\n", strerror(err));
    }
    sleep(0);
    printf("master join success, tid 0x%x, reval %ld\n", (unsigned int)tid, (long int)reval);
    return 0;
}
