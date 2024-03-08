#include <spider.h>

int main(void)
{
    int sock;
    char request[4096];
    url_t node;
    url_t tmpnode;
    ssl_t* ssl = NULL;
    result_fd = open("Result.html", O_RDWR | O_CREAT, 0664);
    Save_result(NULL, NULL, NULL); // 写入html头部信息
    // 创建初始化双队列
    container_t* uct = NULL;
    container_t* pct = NULL;
    uct = Container_create(10000);
    pct = Container_create(Result_Max);
    char* url = "https://baike.baidu.com/item/C%E8%AF%AD%E8%A8%80/105958?fr=ge_ala";
    strcpy(node.origin, url);
    
    /* 1. 种子url去重验证 */
    if (Remove_duplication(uct, pct, url))
    {
        Container_set(uct, node); // 验证成功入队
    }
    while (uct->cur > 0 && pct->cur < Result_Max)
    {
        printf("进入循环\n");
        if (uct->cur >= 600)
        {
            printf("shutdown is %d close\n", Shutdown);
            Shutdown = 0;
        }
        else if (uct->cur <= 100)
        {
            printf("shutdown is %d open\n", Shutdown);
            Shutdown = 1;
        }
        Container_get(uct, &tmpnode); // 出队处理
        sock = Net_initialzer();
        Analytical_url(&tmpnode);
        Connect_server(sock, tmpnode);
        Create_request(request, tmpnode);
        if (tmpnode.type)
        {
            ssl = OpenSSL_initializer(sock);
        }
        if ((Download(sock, tmpnode, request, ssl)) == -1)
        {
            continue;
        }
        Container_set(pct, tmpnode); // 入队已处理
        Html_analytical(tmpnode, uct, pct); // html解析
    }
    printf("spider is done, result numer %d\n", result_num);
    return 0;
}