//
// Created by 阮波 on 2023/4/12.
//
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include "comm/log.h"

/*
 *  situation:
 *      server side: two process, `child` and `parent`, both listen on the same `host:port`.
 *      client side: a tcp client connect to `host:port` multiple times
 *
 *  result:
 *      the new connection accepted by `child` or `parent`, not both.
 *
 *
 *  related:
 *      https://en.wikipedia.org/wiki/Thundering_herd_problem
 *      https://wenfh2020.com/2021/10/12/thundering-herd-tcp-reuseport/
 */
namespace nets {

static int reuse_port_tcp_listen(std::string process_name, std::string ip, int port) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0) {
        Log("socket() failed:%d", errno);
        return -1;
    }

    // set socket option: SO_REUSEPORT
    {
        int on = 1;
        int ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
        if(ret == -1) {
            Log("setsockopt() failed:%d", errno);
            close(sock_fd);
            return -1;
        }
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);

    int ret = ::bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1) {
        Log("bind socket[%d] failed:%d", sock_fd, errno);
        close(sock_fd);
        return -1;
    }

    ret = listen(sock_fd, 64);
    if(ret == -1) {
        Log("listen [%d] failed:%d", sock_fd, errno);
        close(sock_fd);
        return -1;
    }

    Log("[%s] listen on %s:%d", process_name.c_str(), ip.c_str(), port);

    int conn_count = 0;
    while (true) {
        // wait for client
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int conn_fd = ::accept(sock_fd, (struct sockaddr*)&client_addr, &client_len);
        if(conn_fd == -1) {
            Log("[%s] accept failed:%d", process_name.c_str(), errno);
            continue;
        }

        Log("[%s] has new connection:%d", process_name.c_str(), conn_fd);

        write(conn_fd, process_name.c_str(), process_name.length());

        close(conn_fd);

        conn_count += 1;
        if(conn_count >= 3) {
            break;
        }
    }

    return sock_fd;
}

void reuse_port_multi_process() {
    Log("\ncreate two process `child` and `parent`, both listen on the same `ip:port`.");

    int pid = -1;
    if((pid = fork()) == -1) {
        Log("fork() failed:%d", errno);
        return;
    }

    std::string ip = "127.0.0.1";
    int port = 9905;

    if(pid == 0) {
        // child process
        //LogLine("[%d]Hello,", getpid());

        int sock_fd = reuse_port_tcp_listen("child", ip, port);
        if(sock_fd > 0) {
            close(sock_fd);
        }

        exit(0);
    } else {
        // parent process
        // wait(NULL);
        //LogLine("[%d]World.", getpid());

        int sock_fd = reuse_port_tcp_listen("parent", ip, port);
        if(sock_fd > 0) {
            close(sock_fd);
        }

        return;
    }
}

}  // end of namespace
