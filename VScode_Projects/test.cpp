#include <iostream>
#include <regex.h>

using namespace std;

int main()
{
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "^1[3-9][0-9]\\{9\\}$", 0);
    if (reti)
    {
        cout << "无法编译" << endl;
        return 1;
    }

    reti = regexec(&regex, "13941660217", 0, NULL, 0);
    if (!reti)
    {
        cout << "匹配成功" << endl;
    }
    else if (reti == REG_NOMATCH)
    {
        cout << "未匹配到符合正则表达式的字符串" << endl;
    }
    else
    {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        cout << "匹配失败" << msgbuf << endl;
        return 1;
    }
    
    regfree(&regex);

    return 0;
}