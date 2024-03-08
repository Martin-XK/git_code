#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
    int sock_array[1020]; // 存储客户端socket
    int readycode; // 就绪数量
    int max_fd; // 最大描述符
    // 初始化数组
    for (int i = 0; i < 1020; i++)
    {
        sock_array[i] = -1;
    }
    // 网络初始化
    struct sockaddr_in saddr, caddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8080);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // sock create
    int server_sock;
    int client_sock;
    int len;
    char buffer[1500];
    char response[1500];
    char cip[16];
    char timebuf[1024];
    time_t tp;
    bzero(buffer, sizeof(buffer));
    bzero(response, sizeof(response));
    bzero(cip, sizeof(cip));
    socklen_t addrlen;
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    // 绑定和监听
    bind(server_sock, (struct sockaddr*)&saddr, sizeof(saddr));
    listen(server_sock, 128);
    max_fd = server_sock; // 记录最大
    // 监听集合
    fd_set set, oset; // 传入传出分离
    FD_ZERO(&set); // 初始化集合
    FD_SET(server_sock, &set); // 设置监听
    printf("select server version 1.0 running...\n");
    while (1)
    {
        oset = set;
        if ((readycode = select(max_fd + 1, &oset, NULL, NULL, NULL)) == -1) // 阻塞监听socket读事件
        {
            perror("select call failed");
        }
        while (readycode) // 循环处理所有就绪
        {
            // 判断就绪
            if (FD_ISSET(server_sock, &oset)) // server_sock就绪
            {
                // 建立连接
                addrlen = sizeof(caddr);
                client_sock = accept(server_sock, (struct sockaddr*)&caddr, &addrlen);
                // 连接成功反馈信息
                inet_ntop(AF_INET, &caddr.sin_addr.s_addr, cip, 16);
                sprintf(response, "hi, %s welcome select server service..", cip);
                send(client_sock, response, strlen(response), MSG_NOSIGNAL);
                bzero(response, sizeof(response));
                // 添加监听 并存储到数组中
                FD_SET(client_sock, &set);
                for (int i = 0; i < 1020; i++)
                {
                    if (sock_array[i] == -1)
                    {
                        sock_array[i] = client_sock;
                        break;
                    }
                }
                // 设置最大sock
                if (max_fd < client_sock)
                {
                    max_fd = client_sock;
                }
                // 将oset设置0
                FD_CLR(server_sock, &oset);
            }
            else // client_sock 就绪
            {
                // 遍历client_sock数组，查找就绪的sock并处理
                for (int i = 0; i < 1020; i++)
                {
                    if (sock_array[i] != -1)
                    {
                        if (FD_ISSET(sock_array[i], &oset))
                        {
                            // 读取处理数据
                            if ((len = recv(sock_array[i], buffer, sizeof(buffer), 0)) > 0)
                            {
                                // 响应结果
                                buffer[strlen(buffer) - 1] = '\0';
                                if ((strcmp(buffer, "time")) == 0)
                                {
                                    bzero(timebuf, 1024);
                                    tp = time(NULL);
                                    ctime_r(&tp, timebuf);
                                    send(sock_array[i], timebuf, strlen(timebuf), MSG_NOSIGNAL);
                                }
                                else
                                {
                                    send(sock_array[i], "Please try again", 17, MSG_NOSIGNAL);
                                }
                                FD_CLR(sock_array[i], &oset);
                            }
                            if (len == 0)
                            {
                                // 如果客户端退出将它从监听中删除并且从数组中删除
                                FD_CLR(sock_array[i], &set); // 取消监听
                                FD_CLR(sock_array[i], &oset);
                                close(sock_array[i]);
                                sock_array[i] = -1;
                            }
                            break;
                        }
                        
                    }
                    
                }
                
            }
            readycode--;
            
        }
        
    }
    

    return 0;
}