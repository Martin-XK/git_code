#include <pool.h>

pool_t* thread_pool_create(int tmax, int tmin, int qmax)
{
    // 对线程池类初始化，申请空间，按最小阈值创建消费者并且创建管理者
    pool_t* pt = NULL;
    if ((pt = malloc(sizeof(pool_t))) == NULL);
    {
        perror("thread_pool_create, malloc pool failed");
    }
    pt->thread_shutdown = 1;
    pt->thread_max = tmax;
    pt->thread_min = tmin;
    pt->thread_alive = 0;
    pt->thread_busy = 0;
    pt->exit_code = 0;
    // 创建队列
    if ((pt->queue = malloc(sizeof(business_t) * qmax)) == NULL)
    {
        perror("thread_pool_create, malloc queue failed");
    }
    pt->front = 0;
    pt->rear = 0;
    pt->max = qmax;
    pt->cur = 0;
    if ((pt->ctids = malloc(sizeof(pthread_t) * tmax)) == NULL)
    {
        perror("thread_pool_create, malloc ctids failed");
    }
    // 初始化ctids
    bzero(pt->ctids, sizeof(pthread_t) * tmax); //初始化为0
    if (pthread_mutex_init(&(pt->lock), NULL) != 0 || pthread_cond_init(&(pt->Not_Full), NULL) != 0 || pthread_cond_init(&(pt->Not_Empty), NULL) != 0)
    {
        printf("thread_pool_create, init lock or cond failed\n");
    }
    // 预创建消费者
    int err;
    for (int i = 0; i < tmin; i++)
    {
        if ((err = pthread_create(&pt->ctids[i], NULL, NULL, NULL)) > 0)
        {
            printf("thread_pool_create, create customer failed: %s\n", strerror(err));
        }
        else
        {
            ++(pt->thread_alive);
        }
    }
    // 管理线程
    if ((err = pthread_create(&pt->mtid, NULL, NULL, NULL)) > 0)
    {
        printf("thread_pool_create, create manager failed: %s\n", strerror(err));
    }
    return pt;
}