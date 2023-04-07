//
// Created by 阮波 on 2023/4/7.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include "comm/log.h"


namespace nets {

void tcp_server() {
    int sock_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1) {
        Log("socket() failed");
        return;
    }

    int on = 1;
    int ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));
    if(ret == -1) {
        Log("setsockopt failed:%d", errno);
        close(sock_fd);
        return;
    }

    uint16_t listen_port = 9901;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = listen_port;

    ret = ::bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ret < 0) {
        Log("bind %d failed:%d", sock_fd, errno);
        close(sock_fd);
        return;
    }

    int backlog = 64;
    ret = ::listen(sock_fd, backlog);
    if(ret < 0) {
        Log("listen failed");
        close(sock_fd);
        return;
    }

    Log("listen on port:%d", listen_port);

}


} // end of namespace
