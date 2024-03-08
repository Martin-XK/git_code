#include <spider.h>

int Analytical_url(url_t* node)
{
    bzero(node->domain, 1024);
    bzero(node->save_path, 1024);
    bzero(node->name, 1024);
    bzero(node->ip, 16);
    
    // 1. 辨别协议类型
    const char* head[] = {"http://", "https://", NULL};
    int flag = 0; // 偏移下标
    int sflag = 0; // 存储下标
    int start = 0; // 存储位置
    int size = 0;

    if (strncmp(node->origin, head[0], strlen(head[0])) == 0)
    {
        node->type = 0;
        node->port = 80;
        start = strlen(head[0]);
    }
    else
    {
        node->type = 1;
        node->port = 443;
        start = strlen(head[1]);
    }
    // 2. 获取域名
    for (flag = start; node->origin[flag] != '/'; flag++)
    {
        node->domain[sflag] = node->origin[flag];
        sflag++;
    }
    sflag = 0;
    // 3. 获取文件名长度
    for (flag = strlen(node->origin); node->origin[flag] != '/'; flag--, size++);
    // 4. 获取文件名
    for (flag = strlen(node->origin) - size + 1; node->origin[flag] != '\0'; flag++)
    {
        node->name[sflag] = node->origin[flag];
        sflag++;
    }
    // 5. 存储路径
    sflag = 0;
    for (flag = start + strlen(node->domain); flag < strlen(node->origin) - size + 1; flag++)
    {
        node->save_path[sflag] = node->origin[flag];
        sflag++;
    }
    // 6. DNS函数获取ip
    struct hostent* ent = NULL;
    if ((ent = gethostbyname(node->domain)) == NULL)
    {
        printf("analytical url, get ip failed\n");
        exit(0);
    }
    else
    {
        inet_ntop(AF_INET, ent->h_addr_list[0], node->ip, 16);
    }
    printf("[ download ] [ step 01 ] Analytcial url success:\norigin %s\ndomain %s\npath %s\nname %s\nip %s\n type %d\nport %d\n", node->origin, node->domain, node->save_path, node->name, node->ip, node->type, node->port);
    return 0;
}