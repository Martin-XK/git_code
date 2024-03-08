#include <spider.h>

container_t* Container_create(int Max)
{
    container_t* ct = NULL;
    if ((ct = (container_t*)malloc(sizeof(container_t))) == NULL)
    {
        perror("Container_create malloc failed");
        return NULL;
    }
    if ((ct->list = (url_t*)malloc(sizeof(url_t)*Max)) == NULL)
    {
        perror("Container_create malloc list failed");
        return NULL;
    }
    
    ct->front = 0;
    ct->rear = 0;
    ct->cur = 0;
    ct->max = Max;
    return ct;
}