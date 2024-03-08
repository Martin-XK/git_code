#include <server.h>

void* thread_wait(void* arg)
{
    // 进行捕捉
    struct sigaction act, oact;
    pthread_detach(pthread_self());
    act.sa_handler = sig_wait;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, &oact);
    // 解除屏蔽
    sigprocmask(SIG_SETMASK, &act.sa_mask, NULL);
    // 等待信号回收
    printf("wait thread 0x%x waiting...\n", (unsigned int)pthread_self());
    while (1)
    {
        sleep(1);
    }
    pthread_exit(NULL);
}