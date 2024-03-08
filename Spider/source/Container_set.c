#include <spider.h>

int Container_set(container_t* ct, url_t node)
{
    printf("入队\n");
    if (ct->cur == ct->max)
    {
        return -1;
    }
    ct->list[ct->front] = node;
    ct->front = (ct->front + 1) % ct->max;
    ct->cur += 1;
    printf("入队返回\n");
    return 0;
}