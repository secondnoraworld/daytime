/*
 *     daytime.c
 *
 *     Usage: daytime ip_address port_number
 *
 *     Gets and displays the time of a remote server
 *
 *     ip_address: IP address for a remote server
 *     port_number: Port number
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

int main(int argc, char *argv[])
{
    int s;
    struct sockaddr_in sa;
    char buf[MAX_BUF_SIZE + 1];
    int len;

    if (argc != 3) {
        fprintf(stderr, "Usage: daytime ip_adrress port_number\n");
        exit(1);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }

    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &sa.sin_addr) <= 0) {
        perror("inet_pton error");
        exit(1);
    }

    if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        perror("connect error");
        exit(1);
    }

    while ((len = read(s, buf, MAX_BUF_SIZE)) > 0) {
        buf[len] = '\0';
        printf(buf);
    }
    if (len < 0) {
        perror("read error");
    }

    close(s);
}

