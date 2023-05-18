//
// Created by 阮波 on 2023/5/12.
//

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "comm/log.h"


namespace nets {

static int tcp_listen(int listen_port) {
    int sock_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1) {
        Log("socket() failed");
        return -1;
    }

    // allow reusable
    {
        int on = 1;
        int ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));
        if(ret == -1) {
            Log("setsockopt failed:%d", errno);
            close(sock_fd);
            return -1;
        }
    }

    // set non-blocking
    {
        int on = 1;
        int ret = ioctl(sock_fd, FIONBIO, (char*)&on);
        if(ret < 0) {
            Log("ioctl failed:%d", errno);
            close(sock_fd);
            return -1;
        }
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(listen_port);

    int ret = ::bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ret < 0) {
        Log("bind %d failed:%d", sock_fd, errno);
        close(sock_fd);
        return -1;
    }

    int backlog = 64;
    ret = ::listen(sock_fd, backlog);
    if(ret < 0) {
        Log("listen failed");
        close(sock_fd);
        return -1;
    }

    Log("listen on port:%d", listen_port);

    return sock_fd;
}


void select_tcp_server() {
    const int listen_port = 1001;
    int listen_fd = tcp_listen(listen_port);
    if(listen_port == -1) {
        return;
    }

    struct fd_set master_set, working_set;

    FD_ZERO(&master_set);
    FD_SET(listen_fd, &master_set);

    struct timeval timeout;  // on minute
    timeout.tv_sec = 1 * 60;
    timeout.tv_usec = 0;

    int max_fd = listen_fd;
    int new_fd = -1;
    char   buffer[1024];
    bool close_conns = false;
    bool running = true;

    do {
        memcpy(&working_set, &master_set, sizeof(master_set));
        int ret = select(max_fd + 1, &working_set, NULL, NULL, &timeout);
        if(ret < 0) {
            Log("select() failed:%d", errno);
            break;
        }
        if(ret == 0) {
            Log("select() timeout.");
            continue;
        }

        int fd_ready = ret;
        for(int i=0; i<=max_fd && fd_ready > 0; ++i) {
            if(FD_ISSET(i, &working_set)) {
                fd_ready -= 1;

                if(i == listen_fd) {
                    Log("listen fd:%d is readable", i);

                    do {
                        new_fd = accept(listen_fd, NULL, NULL);
                        if(new_fd < 0) {
                            if(errno != EWOULDBLOCK) {
                                Log("accept() failed:%d", errno);
                                running = false;
                            }
                            break;
                        }
                    } while (new_fd != -1);
                } else {
                    Log("fd:%d is readable", i);

                    do {
                        ret = recv(i, buffer, sizeof(buffer), 0);
                        if(ret < 0) {
                            if(errno != EWOULDBLOCK) {
                                Log("recv() failed:%d", errno);
                                close_conns = true;
                            }
                            break;
                        }

                        if(ret == 0) {
                            Log("connection closed.");
                            close_conns = true;
                            break;
                        }

                        int recv_bytes = ret;
                        Log("%d bytes data received", recv_bytes);

                        ret = send(i, buffer, recv_bytes, 0);
                        if(ret < 0) {
                            Log("send() failed:%d", errno);
                            close_conns = true;
                            break;
                        }
                    } while (true);

                    if(close_conns) {
                        close(i);
                        FD_CLR(i, &master_set);
                        if(i == max_fd) {
                            while (FD_ISSET(max_fd, &master_set) == false) {
                                max_fd -= 1;
                            }
                        }
                    }
                }
            }
        }

    } while (running == true);

    // clean all the sockets that opened
    for(int i=0; i <= max_fd; ++i) {
        if(FD_ISSET(i, &master_set)) {
            close(i);
        }
    }

}

}  // end of namespace
