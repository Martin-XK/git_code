#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define SHUTDOWN 1

// extern int clientsock[10000];

int net_initializer(void);
int first_response(int, struct sockaddr_in);
int recv_request(int);
int server_start(void);