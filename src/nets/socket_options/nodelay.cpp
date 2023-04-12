//
// Created by 阮波 on 2023/4/12.
//
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>   // TCP_NODELAY
#include <unistd.h>
#include "comm/log.h"


namespace nets {

void tcp_nodelay() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd == -1) {
        Log("socket() failed:%d", errno);
        return;
    }

    {
        int on = 1;
        int ret = setsockopt(sock_fd, IPPROTO_TCP, TCP_NODELAY, (char*)&on, sizeof(on));
        if(ret == -1) {
            Log("setsockopt(%d, IPPROTO_TCP, TCP_NODELAY) failed.", sock_fd);
            close(sock_fd);
            return;
        }
    }
}

}