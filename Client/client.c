#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

int main(void)
{
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr.s_addr);
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("sock create failed");
    }
    if ((connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) == -1)
    {
        perror("connect failed");
    }
    // 读取连接信息
    char buffer[1500];
    bzero(buffer, sizeof(buffer));
    if ((recv(sockfd, buffer, sizeof(buffer), 0)) == -1)
    {
        perror("recv call failed");
    }
    printf("%s\n", buffer);
    // 客户端读取标准输入， 发送给服务器
    bzero(buffer, sizeof(buffer));
    while ((fgets(buffer, sizeof(buffer), stdin)) != NULL)
    {
        // 发送请求
        send(sockfd, buffer, strlen(buffer), MSG_NOSIGNAL);
        bzero(buffer, sizeof(buffer));
        // 接收响应
        recv(sockfd, buffer, sizeof(buffer), 0);
        // 显示响应
        printf("%s\n", buffer);
    }
    close(sockfd);
    return 0;
}