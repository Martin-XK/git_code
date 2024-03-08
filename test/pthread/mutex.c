#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <signal.h>

int i;
pthread_mutex_t lock; //全局互斥锁

void* twk(void* arg)
{
    int tmp;
    for (int j = 0; j < 5000; j++)
    {
        // lock
        pthread_mutex_lock(&lock);
        tmp = i;
        printf("thread 0x%x i++ %d\n", (unsigned int)pthread_self(), ++tmp);
        i = tmp;
        pthread_mutex_unlock(&lock);
        // unlock
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    // 初始化锁
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < 2; i++)
    {                   
        pthread_create(&tid, NULL, twk, NULL);
    }
    // 确保锁使用完毕再进行释放
    while (1)
    {
        sleep(1);
    }
    return 0;
}