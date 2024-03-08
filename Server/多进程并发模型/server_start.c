#include <server.h>

int server_start(void)
{
    int sockfd, csock;
    struct sockaddr_in client_addr;
    pid_t pid;
    socklen_t addrlen;
    sockfd = net_initializer(); //网络初始化

    printf("process tcp server running...\n");
    // 设置屏蔽字
    sigset_t set, oset;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_SETMASK, &set, &oset);
    // 回收线程创建
    pthread_t tid;
    int err;
    if ((err = pthread_create(&tid, NULL, thread_wait, NULL)) > 0)
    {
        printf("wait thread create error: %s\n", strerror(err));
        exit(0);
    }
    
    while (SHUTDOWN)
    {
        addrlen = sizeof(client_addr);
        // 非阻塞等待连接
        if((csock = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen)) > 0) //阻塞等待连接
        {
            pid = fork();
            if (pid > 0)
            {
                first_response(csock, client_addr); // 父进程完成连接与首次响应
            }
            else if (pid == 0)
            {
                recv_request(csock); // 子进程处理客户端请求
            }
            else
            {
                perror("fork call failed");
                exit(0);
            }
        }
    }
    close(sockfd);
    printf("server its done\n");
    return 0;
}