//
// Created by 阮波 on 2023/4/11.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>   // close()
#include <strings.h>  // bzero()
#include "comm/log.h"

namespace nets {

static int tcp_listen(const char* ip, int port, bool reuse) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0) {
        Log("socket() failed:%d", errno);
        //perror(NULL);
        return -1;
    }

    // set socket option: SO_REUSEPORT
    {
        int on = 0;
        if(reuse) {
            on = 1;
        }
        int ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
        if(ret == -1) {
            Log("setsockopt() failed:%d", errno);
            //perror(NULL);
            close(sock_fd);
            return -1;
        }
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    int ret = ::bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1) {
        Log("bind socket[%d] failed:%d", sock_fd, errno);
        //perror(NULL);
        close(sock_fd);
        return -1;
    }

    ret = listen(sock_fd, 64);
    if(ret == -1) {
        Log("listen [%d] failed:%d", sock_fd, errno);
        //perror(NULL);
        close(sock_fd);
        return -1;
    }

    return sock_fd;
}

/*
 * listen 127.0.0.1:9903 two times without SO_REUSEPORT option set.
 */
static void reuse_port_case_1() {
    const char* ip = "127.0.0.1";
    const int port = 9903;
    const bool is_reuse = false;

    Log("listen %s:%d two times without SO_REUSEPORT option set.", ip, port);

    int sock_fd_1 = -1, sock_fd_2 = -1;
    {
        sock_fd_1 = tcp_listen(ip, port, is_reuse);
        if(sock_fd_1 > 0) {
            Log("the first listen is OK.")
        }
    }

    Log("listen %s:%d again", ip, port);
    {
        sock_fd_2 = tcp_listen(ip, port ,is_reuse);
        if(sock_fd_2 == -1) {
            Log("the second listen is failed, which is expected.")
        }
    }

    if(sock_fd_1 > 0) {
        close(sock_fd_1);
    }
    if(sock_fd_2 > 0) {
        close(sock_fd_2);
    }
}

/*
 * listen 127.0.0.1:9904 two times with SO_REUSEPORT option set.
 */
static void reuse_port_case_2() {
    const char* ip = "127.0.0.1";
    const int port = 9904;
    const bool is_reuse = true;

    Log("\nlisten %s:%d two times with SO_REUSEPORT option set.", ip, port);
    int sock_fd_1 = -1, sock_fd_2 = -1;
    Log("listen %s:%d", ip, port);
    {
        sock_fd_1 = tcp_listen(ip, port, is_reuse);
        if(sock_fd_1 > 0) {
            Log("the first listen is OK.")
        }
    }

    Log("listen %s:%d again", ip, port);
    {
        sock_fd_2 = tcp_listen(ip, port ,is_reuse);
        if(sock_fd_2 > 0) {
            Log("the second listen is OK two, which is expected.")
        }
    }

    if(sock_fd_1 > 0) {
        close(sock_fd_1);
    }
    if(sock_fd_2 > 0) {
        close(sock_fd_2);
    }
}

void reuse_port() {
    reuse_port_case_1();

    reuse_port_case_2();
}

}  // end of namespace
