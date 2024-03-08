#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h> // 访问DNS域名解析
#include <regex.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/mman.h>

#define Result_Max 50

int result_num;
int result_fd;
int Shutdown; // 为0表示暂停解析新链接，1恢复解析

typedef struct
{
    SSL* sslsock; // 安全套接字用于后续安全传输
    SSL_CTX* sslctx; // 认证信息，上下文，包含版本信息等
}ssl_t;

typedef struct
{
    char origin[8192];
    char domain[1024];
    char save_path[1024];
    char name[1024];
    char ip[16];
    int type; // http = 0  https = 1
    int port; // 80 or 443
}url_t;

typedef struct
{
    url_t* list;
    int front;
    int rear;
    int cur;
    int max;
}container_t;

int Analytical_url(url_t*); // url解析模块
int Net_initialzer(void); // 网络初始化
int Connect_server(int, url_t); // 连接web服务器
int Create_request(char*, url_t); // 创建请求
int Get_code(const char* response); // 从响应头中获取状态码
int Download(int sock, url_t node, char* request, ssl_t* ssl); // 下载
ssl_t* OpenSSL_initializer(int sock); // 对openssl进行初始化以及认证过程

container_t* Container_create(int Max); // 队列初始化
int Container_set(container_t*, url_t node); // 入队操作
int Container_get(container_t*, url_t* node); // 出队操作
int Remove_duplication(container_t*, container_t*, const char* link); // 去重验证，无重复返回1，否则返回0
int Html_analytical(url_t node, container_t* uct, container_t* pct); // html网页源码处理
int Save_result(const char* title, const char* description, const char* link);