#include <spider.h>

int Get_code(const char* response)
{
    // HTTP/1.1 200 OK
    regex_t reg;
    regmatch_t match[2];
    char result[1024];
    int code;
    bzero(result, sizeof(result));
    const char* regstr = "HTTP/1.1 \\([^\r]\\+\\?\\)\r\n";
    regcomp(&reg, regstr, 0);
    if ((regexec(&reg, response, 2, match, 0)) == 0)
    {
        snprintf(result, match[1].rm_eo - match[1].rm_so + 1, "%s", response + match[1].rm_so);
        sscanf(result, "%d ", &code);
        regfree(&reg);
        return code;
    }
    printf("Get_code regexec failed\n");
    regfree(&reg);
    return -1;
}