#include <server.h>

int first_response(int sockfd, struct sockaddr_in caddr)
{
    char cip[16];
    char response[1500];
    bzero(cip, 16);
    bzero (response,1500);
    inet_ntop(AF_INET, &caddr, cip, 16);
    printf("connection success, client ip %s client port %d\n", cip, ntohs(caddr.sin_port));
    sprintf(response, "hi, %s welcome my test tcp server.", cip);
    send(sockfd, response, strlen(response), MSG_NOSIGNAL);
    return 0;
}