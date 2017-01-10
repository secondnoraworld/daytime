/*
 *     daytimed.c
 *
 *     Usage: daytimed port_number
 *
 *     port_number: Port number
 *
 *     Tells a remote client the time of this server
 *
 *     Copyright (C) 2006 Katsuhisa Maruyama (maru@cs.ritsumei.ac.jp)
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

/*for 64bit OS*/
#include <arpa/inet.h> //inet_ntoa()
#include <time.h>      //time(),ctime()
#include <unistd.h>    //write(),close()

#define MAX_BUF_SIZE 256
#define BACKLOG 5

int main(int argc, char *argv[])
{
    int s;
    struct sockaddr_in sa;
    char buf[MAX_BUF_SIZE + 1];
    int len;
    int c;
    struct sockaddr_in csa;
    int n;
    time_t seconds;
#ifndef NOREUSEADDR
    int nonzero = 1;
#endif

    if (argc != 2) {
        fprintf(stderr, "Usage: daytimed port_number\n");
        exit(1);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[1]));
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

#ifndef NOREUSEADDR
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &nonzero, sizeof(nonzero));
#endif

    if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("bind error");
        exit(1);
    }

    if (listen(s, BACKLOG) < 0) {
        perror("listen error");
        exit(1);
    }


    while (1) {
        n = sizeof(csa);
        if ((c = accept(s, (struct sockaddr *)&csa, (socklen_t *)&n)) < 0) {
            perror("connect error");
            exit(1);
        }

        printf("Connected from %s port %d\n", inet_ntoa(csa.sin_addr), ntohs(csa.sin_port));
        
        seconds = time(NULL);
        snprintf(buf, MAX_BUF_SIZE, "%s\r\n", ctime(&seconds));
        write(c, buf, strlen(buf));
        close(c);
    }
}
