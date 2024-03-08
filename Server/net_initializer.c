#include <server.h>

int net_initializer(void)
{
    int sockfd;
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("net_initializer, call socket failed");
    }
    if ((bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr))) == -1)
    {
        perror("net_initializer, call bind failed");
    }
    listen(sockfd, 128);
    return sockfd;
}