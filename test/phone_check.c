#include <stdio.h>
#include <regex.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("pram error, please try again...\n");
        return 1;
    }

    regex_t regex;
    int reti;
    char msgbuf[100];
    // 
    reti = regcomp(&regex, "^1[3-9][0-9]\\{9\\}$", 0);
    if (reti)
    {
        printf("无法编译");
        return 1;
    }

    reti = regexec(&regex, argv[1], 0, NULL, 0);
    if (!reti)
    {
        printf("匹配成功");
    }
    else if (reti == REG_NOMATCH)
    {
        printf("未匹配到符合正则表达式的字符串");
    }
    else
    {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        printf("匹配失败，%s\n", msgbuf);
        return 1;
    }
    
    regfree(&regex);

    return 0;
}