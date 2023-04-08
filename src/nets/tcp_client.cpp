//
// Created by 阮波 on 2023/4/8.
//
#include <sys/socket.h>
#include <arpa/inet.h>
#include "comm/log.h"


namespace nets {

int tcp_connect_to(const char* ip, int port) {
    int sock_fd = 0;

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd == -1) {
        Log("socket() failed:%d", errno);
        perror(NULL);
        return -1;
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    if(connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        Log("connect to server failed:%d", errno);
        perror(NULL);
        return -1;
    }

    return sock_fd;
}


}  // end of namespace