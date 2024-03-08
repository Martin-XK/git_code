#include <spider.h>

int Remove_duplication(container_t* uct, container_t* pct, const char* link)
{
    int flag;
    flag = uct->rear;

    while (flag % uct->max != uct->front)
    {
        if ((strncmp(uct->list[flag].origin, link, strlen(link))) == 0)
        {
            return 0;
        }
        flag++;
    }
    flag = pct->rear;

    while (flag % pct->max != pct->front)
    {
        if ((strncmp(pct->list[flag].origin, link, strlen(link))) == 0)
        {
            return 0;
        }
        flag++;
    }
    return 1;
}