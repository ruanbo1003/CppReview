//
// Created by 阮波 on 2023/4/7.
//

#ifndef CPPREVIEW_NETS_HEAD_H
#define CPPREVIEW_NETS_HEAD_H

namespace nets {

void tcp_server();
void reuse_addr();
void reuse_port();
void buf_size();


void tests() {
//    tcp_server();

//    reuse_addr();

    reuse_port();

    buf_size();

}

}

#endif //CPPREVIEW_NETS_HEAD_H
