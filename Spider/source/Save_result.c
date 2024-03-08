#include<spider.h>

int Save_result(const char* title, const char* description, const char* link)
{
    char result[10000];
    bzero(result, sizeof(result));
    const char* start = "<html>\r\n<head>\r\n<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\">\r\n</head>\r\n<table border=\"1\" cellspacing=\"0\" cellpadding=\"0\" width=\"1900\">\r\n<caption>百科数据集</caption>\r\n<tr><th>id</th><th>词条名</th><th>描述</th><th>超链接</th><tr>\r\n";
    const char* end = "</table>\r\n</html>\r\n";

    if (result_num == 0)
    {
        write(result_fd, start, strlen(start));
        return 0;
    }

    // 拼写接入
    // html语言中的超链接标签，可以点击跳转访问
    // <a href="链接地址">超链接标题</a>
    sprintf(result, "<tr><td>%d</td><td>%s</td><td>%s</td><td><a href=\"%s\">%s</a></td></tr>\r\n", result_num, title, description, link, link);
    write(result_fd, result, strlen(result));

    if (result_num == 0)
    {
        write(result_fd, end, strlen(end));
        close(result_fd);
        return 0;
    }
    
}