#include <server.h>

int server_start(void)
{
    int sockfd, csock;
    struct sockaddr_in client_addr;
    
    for (int i = 0; i < 10000; i++)
    {
        clientsock[i] = -1;
    }
    
    socklen_t addrlen;
    sockfd = net_initializer(); //网络初始化

    // 将sockfd变为非阻塞
    int flag;
    fcntl(sockfd, F_GETFL, &flag);
    flag |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, flag);

    printf("process tcp server running...\n");
    while (SHUTDOWN)
    {
        addrlen = sizeof(client_addr);
        // 非阻塞等待连接
        if((csock = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen)) > 0) //阻塞等待连接
        {
            for (int i = 0; i < 10000; i++)
            {
                if (clientsock[i] == -1)
                {
                    clientsock[i] = csock;
                        break;
                }
            }
            first_response(csock, client_addr); //连接成功首次反馈信息
        }
        if (csock == -1)
        {
            if (errno == EAGAIN)
            {
                recv_request(csock); // 非阻塞遍历读取客户端请求
            }
            else
            {
                perror("accept call failed");
            }
        }
    }
    close(sockfd);
    printf("server its done\n");
    return 0;
}