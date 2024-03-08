#include <server.h>

void sig_wait(int n)
{
    pid_t zpid;
    while ((zpid = waitpid(-1, NULL, WNOHANG)) != -1)
    {
        if (zpid > 0)
        {
            printf("thread wait success, zpid %d\n", zpid);
        }
        else
        {
            
        }
    }
}