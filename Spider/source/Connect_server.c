#include <spider.h>

int Connect_server(int sock, url_t node)
{
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, node.ip, &serverAddr.sin_addr.s_addr);
    serverAddr.sin_port = htons(node.port);
    if ((connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) == 0)
    {
        printf("[ download ][ step 03 ] Connect server success..\n");
    }
    else
    {
        perror("Connect_server connect failed");
        return -1;
    }
    return 0;
}