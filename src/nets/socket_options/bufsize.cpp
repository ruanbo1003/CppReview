//
// Created by 阮波 on 2023/4/11.
//
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>   // close()

#include "comm/log.h"

namespace nets {

/*
 *  MacOS default value:
 *      sysctl net.inet.tcp.recvspace : 131072
 *      sysctl net.inet.tcp.sendspace : 131072
 *
 *  Ubuntu defalut value:
 *      /proc/sys/net/ipv4/tcp_rmem : 131072
 *      /proc/sys/net/ipv4/tcp_wmem : 16384
 */

void buf_size() {
    Log("\nsocket send/receive buffer size");

    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd == -1) {
        Log("socket() failed:%d", errno);
        return;
    }

    // SO_SNDBUF: send buf size
    {
        int default_send_buf = 0;
        socklen_t t = sizeof(default_send_buf);
        int ret = getsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &default_send_buf, &t);
        if(ret == -1) {
            Log("getsockopt(%d) failed:%d", sock_fd, errno);
            close(sock_fd);
            return;
        }

        Log("default send buf size:%d", default_send_buf);
    }

    // SO_RCVBUF: receive buf size
    {
        int default_receive_buf = 0;
        socklen_t t = sizeof(default_receive_buf);
        int ret = getsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, &default_receive_buf, &t);
        if(ret == -1) {
            Log("getsockopt(%d) failed:%d", sock_fd, errno);
            close(sock_fd);
            return;
        }

        Log("default receive buf size:%d", default_receive_buf);
    }

    close(sock_fd);
}

}