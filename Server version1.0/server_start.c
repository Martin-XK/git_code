#include <server.h>

int server_start(void)
{
    int sockfd, csock;
    struct sockaddr_in client_addr;
    socklen_t addrlen;
    sockfd = net_initializer(); //网络初始化
    printf("process tcp server running...\n");
    while (SHUTDOWN)
    {
        addrlen = sizeof(client_addr);
        if((csock = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen)) == -1) //阻塞等待连接
        {
            perror("accept call failed");
        }
        first_response(csock, client_addr); //连接成功首次反馈信息
        recv_request(csock); // 非阻塞遍历读取客户端请求
    }
    close(sockfd);
    printf("server its done\n");
    return 0;
}