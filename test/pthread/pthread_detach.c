#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void* twk(void* arg)
{
    printf("thread 0x%x running...\n", (unsigned int)pthread_self());
    pthread_detach(pthread_self()); // 设置分离
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    int err;
    if ((err = pthread_create(&tid, NULL, twk, NULL)) > 0)
    {
        printf("create thread failed: %s\n", strerror(err));
    }
    sleep(1);
    if ((err = pthread_join(tid, NULL)) > 0)
    {
        printf("create join failed: %s\n", strerror(err));
    }
    else
    {
        printf("join success..\n");
    }
    return 0;
}