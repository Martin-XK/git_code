#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SERVER PORT 880
#define SERVER IP "127.0.0.1"
#define BACKLOG 128
#define TIMEOUT 2
#define BUFSIZE 1500
#define PSIZE 16
#define SHUTDOWN 1
/*测试demo ，支持基本tcp链接，用户链接成功后，向用户发送服务器的反馈信息*/

/*字符简易处理，小写转大写*/

/*用户发送localtime字段，服务器反馈最新网络时间*/