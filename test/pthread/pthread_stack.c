#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <signal.h>

void* twk(void* arg)
{
    while (1)
    {
        sleep(1);
    }
}

int main()
{
    int detachstate;
    int flag = 0;
    int err;
    pthread_t tid;
    /*定义属性*/
    pthread_attr_t attr;
    /*初始化属性*/
    pthread_attr_init(&attr);
    // 查看栈信息
    void* stackaddr;
    size_t stacksize;
    pthread_attr_getstack(&attr, &stackaddr, &stacksize);
    printf("stack info: addr %p, size %d\n", stackaddr, (int)stacksize);
    stacksize = 0x100000;
    // 修改属性提高好线程的方式之对x86系统有效
    while (1)
    {
        if ((stackaddr = (void*)malloc(stacksize)) == NULL)
        {
            perror("malloc failed");
            exit(0);
        }
        pthread_attr_setstack(&attr, stackaddr, stacksize);
        if ((err = pthread_create(&tid, NULL, twk, NULL)) > 0)
        {
            printf("create failed: %s\n",strerror(err));
            exit(0);
        }
        printf("%d\n", ++flag);
    }
    pthread_attr_destroy(&attr);
    return 0;
}