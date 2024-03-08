#include <spider.h>

int Download(int sock, url_t node, char* request, ssl_t* ssl)
{
    char response[4096];
    char buffer[8192];
    int len;
    char* pos = NULL;
    int code;
    int fd;
    bzero(response, sizeof(response));
    bzero(buffer, sizeof(buffer));
    if (!ssl)
    {
        /*send request*/
        send(sock, request, strlen(request), MSG_NOSIGNAL);
        printf("[ download ][ step 05 ] send request\n");
        /*first recv*/
        if ((len = recv(sock, buffer, sizeof(buffer), 0)) == -1)
        {
            perror("recv response failed");
            return -1;
        }
        /*find response head*/
        if ((pos = strstr(buffer, "\r\n\r\n")) == NULL)
        {
            printf("strstr find \\r\\n\\r\\n failed\n");
            return -1;
        }
        snprintf(response, pos - buffer + 4, "%s", buffer);
        /*get code*/
        code = Get_code(response);
        printf("[ download ][ step 06 ] [ %d ]get response:\n%s", code, response);
        if (code == 200)
        {
            if ((fd = open(node.name, O_RDWR|O_CREAT, 0664)) == -1)
            {
                perror("create file failed");
                return -1;
            }
            write(fd, pos + 4, len - (pos - buffer + 4));
            bzero(buffer, sizeof(buffer));
            while ((len = recv(sock, buffer, sizeof(buffer), 0)) > 0)
            {
                write(fd, buffer, len);
                bzero(buffer, sizeof(buffer));
            }
            close(fd);
            close(sock);
            printf("[ download ][ step 07 ] [ %d ] Download success\n", code);
            return 0;
        }
        else
        {
            printf("[ download ][ step 07 ] [ %d ] Download error\n", code);
            close(sock);
            return -1;
        }
    }
    else
    {
        /*send request*/
        SSL_write(ssl->sslsock, request, strlen(request));
        printf("[ download https ][ step 05 ] send request\n");
        /*first recv*/
        if ((len = SSL_read(ssl->sslsock, buffer, sizeof(buffer))) == -1)
        {
            perror("recv response failed");
            return -1;
        }
        /*find response head*/
        if ((pos = strstr(buffer, "\r\n\r\n")) == NULL)
        {
            printf("strstr find \\r\\n\\r\\n failed\n");
            return -1;
        }
        snprintf(response, pos - buffer + 4, "%s", buffer);
        /*get code*/
        code = Get_code(response);
        printf("[ download ][ step 06 ] [ %d ]get response:\n%s", code, response);
        if (code == 200)
        {
            if ((fd = open(node.name, O_RDWR|O_CREAT, 0664)) == -1)
            {
                perror("create file failed");
                return -1;
            }
            write(fd, pos + 4, len - (pos - buffer + 4));
            bzero(buffer, sizeof(buffer));
            while ((len = SSL_read(ssl->sslsock, buffer, sizeof(buffer))) > 0)
            {
                write(fd, buffer, len);
                bzero(buffer, sizeof(buffer));
            }
            close(fd);
            close(sock);
            printf("[ download ][ step 07 ] [ %d ] Download success\n", code);
            return 0;
        }
        else
        {
            printf("[ download ][ step 07 ] [ %d ] Download error\n", code);
            close(sock);
            return -1;
        }
    }
    
    
}