#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <time.h>

// business_t 业务类型
typedef struct
{
    void* (*task)(void *arg);
    void* arg;
}business_t;

// pool_t 线程池类型
typedef struct
{
    int thread_shutdown; // 线程池开关
    int thread_max; // 线程池的最大线程数
    int thread_min; // 线程池的最小线程数
    int thread_alive; // 存活有效的线程数量
    int thread_busy; // 繁忙线程数量
    int exit_code; // 缩减码

    business_t* queue; // 环形任务队列
    int front;
    int rear;
    int max;
    int cur;

    pthread_mutex_t lock; //互斥锁
    pthread_cond_t Not_Full; // 生产者条件变量
    pthread_cond_t Not_Empty; // 消费者条件变量
    pthread_t* ctids; // 消费者tid数组
    pthread_t mtid; // 管理者线程id
}pool_t;

pool_t* thread_pool_create(int tmax, int tmin, int qmax);