#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <signal.h>

int code;
pthread_rwlock_t lock;

void* write_thread(void* arg)
{
    while (1)
    {
        pthread_rwlock_wrlock(&lock);
        printf("write thread 0x%x ++code %d\n", (unsigned int)pthread_self(), ++code);
        pthread_rwlock_unlock(&lock);
        usleep(100000);
    }
}

void* read_thread(void* arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&lock);
        printf("write thread 0x%x code %d\n", (unsigned int)pthread_self(), code);
        pthread_rwlock_unlock(&lock);
        usleep(100000);
    }
}

int main()
{
    pthread_t tids[0];
    int i = 0;
    pthread_rwlock_init(&lock, NULL);
    for (i; i < 3; i++)
    {
        pthread_create(&tids[i], NULL, write_thread, NULL);
    }
    for (i; i < 8; i++)
    {
        pthread_create(&tids[i], NULL, read_thread, NULL);
    }
    while (i--)
    {
        pthread_join(tids[i], NULL);
    }
    pthread_rwlock_destroy(&lock);
    return 0;
}