#include <spider.h>

int Create_request(char* request, url_t node)
{
    bzero(request, 4096);
    sprintf(request, "GET %s HTTP/1.1\r\n"\
                     "Accept:text/html,shtml,application/xhtml+xml;q=0.9,image/webp;q=0.8\r\n"\
                     "User-Agent:Mozilla/5.0 (X11; Linux x86_64)\r\n"\
                     "Host:%s\r\n"\
                     "Connection:close\r\n\r\n", node.origin, node.domain);
    printf("[ download ][ step 04 ] Create request success:\n%s\n", request);
    return 0;
}