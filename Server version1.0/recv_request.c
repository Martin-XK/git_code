#include <server.h>

int recv_request(int sockfd)
{
    char response[1500];
    char ctime[1024];
    bzero(response, sizeof(response));
    bzero(ctime, sizeof(ctime));
    int len;
    time_t tp;
    int i = 0;
    while((len = recv(sockfd, response, sizeof(response), 0)) > 0)
    {
        response[strlen(response) - 1] = '\0'; //去除空行
        // if (strncmp(response, "time", strlen(response)) == 0)  // 这里如果写成strlen(response)，客户端发来空内容也会返回时间
        if (strncmp(response, "time", 4) == 0)
        {
            // 反馈时间
            tp = time(NULL);
            ctime_r(&tp, ctime);
            send(sockfd, ctime, strlen(ctime), MSG_NOSIGNAL);
        }
        else
        {
            send(sockfd, "Please try again\n", 16, MSG_NOSIGNAL);
        }
        bzero(response, sizeof(response));
        bzero(ctime, sizeof(ctime));
    }
    if (len == 0) // 表示客户端断开
    {
        printf("client sockfd %d its exiting...\n", sockfd);
        close(sockfd);
    }
    // 如果非阻塞recv返回-1，可以使用errno == EAGAIN
    return 0;
}