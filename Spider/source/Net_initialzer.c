#include <spider.h>

int Net_initialzer(void)
{
    int sock;
    int port = 8080;
    struct sockaddr_in myaddr;
    bzero(&myaddr, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(port);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Net_initialzer Socket call failed");
        return -1;
    }
    if ((bind(sock, (struct sockaddr*)&myaddr, sizeof(myaddr))) == -1)
    {
        perror("Net_initialzer bind call failed");
        return -1;
    }
    printf("[ download ][ step 02 ] Net_initialzer success..\n");
    return sock;
}