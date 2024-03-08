#include <spider.h>

int Html_analytical(url_t node, container_t* uct, container_t* pct)
{
    printf("html解析\n");
    int fd;
    int size;
    char* data = NULL;
    char* cpdata = NULL;
    char h1[1024];
    char desc[8192];
    char link[8192];
    bzero(h1, sizeof(h1));
    bzero(desc, sizeof(desc));
    bzero(link, sizeof(link));
    url_t tmpnode;
    /* 1. 打开映射文件，计算大小 */
    fd = open(node.name, O_RDWR);
    size = lseek(fd, 0, SEEK_END);
    /* 2. 映射 */
    if ((data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    {
        perror("Html_analytical mmap failed");
        return -1;
    }
    cpdata = data;
    close(fd);
    /* 3. 准备正则 */
    regex_t hreg, dreg, lreg;
    regmatch_t hmatch[2];
    regmatch_t dmatch[2];
    regmatch_t lmatch[2];
    regcomp(&hreg, "<h1 [^>]\\+\\?>\\([^<]\\+\\?\\)</h1>", 0);
    regcomp(&dreg, "<meta name=\"description\" content=\"\\([^\"]\\+\\?\\)\">", 0);
    regcomp(&lreg, "<a [^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>[^<]\\+\\?</a>", 0);
    /* 标题与描述的匹配各一次 */
    if ((regexec(&hreg, data, 2, hmatch, 0)) == 0)
    {
        snprintf(h1, hmatch[1].rm_eo - hmatch[1].rm_so + 1, "%s", data + hmatch[1].rm_so);
    }
    if ((regexec(&dreg, data, 2, dmatch, 0)) == 0)
    {
        snprintf(desc, dmatch[1].rm_eo - dmatch[1].rm_so + 1, "%s", data + dmatch[1].rm_so);
    }
    ++result_num;
    Save_result(h1, desc, node.origin); // 写入结果
    // 根据开关决定是否匹配更多词条链接
    if (Shutdown)
    {
        printf("匹配更多\n");
        while ((regexec(&lreg, data, 2, lmatch, 0)) == 0)
        {
            snprintf(link, lmatch[1].rm_eo - lmatch[1].rm_so + 24, "https://baike.baidu.com%s", data + lmatch[1].rm_so);
            if (Remove_duplication(uct, pct, link))
            {
                strcpy(tmpnode.origin, link);
                Container_set(uct, tmpnode);
            }
            bzero(link, sizeof(link));
            data += lmatch[0].rm_eo;
            if (uct->cur + 1 == uct->max)
            {
                printf("uct is full...\n");
                break;
            }
            
        }
        
    }
    unlink(node.name);
    regfree(&hreg);
    regfree(&dreg);
    regfree(&lreg);
    munmap(cpdata, size);
    printf("html解析返回\n");
    return 0;
}