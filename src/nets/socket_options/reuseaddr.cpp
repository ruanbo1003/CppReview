//
// Created by 阮波 on 2023/4/8.
//
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>  // bzero()

#include "comm/log.h"

/*
 * MSL: Maximum Segment Life
 * OSX:
 *      net.inet.tcp.msl = 15000(default)
 *      net.inet.tcp.fin_timeout = 600000(default)
 *
 *      update e.g: sudo sysctl -w net.inet.tcp.msl=20000
 */

namespace nets {

int tcp_connect_to(const char* ip, int port);

static int tcp_listen(const char* ip, int port, bool reuse) {
    int sock_fd = 0, err = 0;
    int backlog = 4;
    struct sockaddr_in addr;

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0) {
        Log("socket failed:%d", errno);
        perror(NULL);
        return -1;
    }

    // set option: SO_REUSEADDR
    {
        int on = 0;
        if(reuse) {
            on = 1;
        }
        int ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if(ret == -1) {
            Log("setsockopt failed:%d", errno);
            perror(NULL);
            close(sock_fd);
            return -1;
        }
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    err = ::bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
    if(err == -1) {
        Log("bind sock_fd[%d], failed:%d", sock_fd, errno);
        perror(NULL);
        close(sock_fd);
        return -1;
    }

    err = listen(sock_fd, backlog);
    if(err == -1) {
        Log("listen sock_fd[%d] failed:%d", sock_fd, errno);
        perror(NULL);
        close(sock_fd);
        return -1;
    }

    return sock_fd;
}


/*
 * do not set SO_REUSEADDR.
 *  1. server listen on 127.0.0.1:9902
 *  2. a client connect to 127.0.0.1:9902
 *  3. server accept the connection
 *  4. server close the connection
 *  5. server close itself
 *  6. sleep 5-seconds
 *  7. server listen on 127.0.0.1:9902 again
 *
 *  result: is_reuse = true: OK
 *          is_reuse = false: Address already in use
 *
 */
static void reuseaddr_case_1() {
    const char* ip = "127.0.0.1";
    const int port = 9902;
    const bool is_reuse = false;

    int sock_fd_1 = tcp_listen(ip, port, is_reuse);
    Log("sock_fd_1:%d", sock_fd_1);
    if(sock_fd_1 == -1) {
        return;
    }

    int client_fd = tcp_connect_to(ip, port);
    if(client_fd == -1) {
        Log("client connect failed");
        close(sock_fd_1);
        return;
    }
    Log("client fd:%d", client_fd);

    int conn_fd = accept(sock_fd_1, NULL, NULL);
    Log("new connection fd:%d", conn_fd);
    if(conn_fd > 0) {
        close(conn_fd);
    }
//    close(client_fd);  // server close client connection

    close(sock_fd_1);
    sleep(4);  // sleep 5-seconds

    int sock_fd_2 = tcp_listen(ip, port, is_reuse);
    Log("sock_fd_2:%d f", sock_fd_2);
    if(sock_fd_2 == -1) {
        Log("listen again - failed");
        Log("=== this is expected - great ===")
        return;
    }

    Log("listen again - success");

    close(sock_fd_2);
}
void reuseaddr() {
    reuseaddr_case_1();

}

} // end of namespace
