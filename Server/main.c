#include <server.h>

int clientsock[10000];

/*单进程服务端 满足基本tcp连接 完成简单数据交互 对于系统时间的请求与响应*/
int main(void)
{
    server_start();
    return 0;
}