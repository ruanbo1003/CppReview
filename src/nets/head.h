//
// Created by 阮波 on 2023/4/7.
//

#ifndef CPPREVIEW_NETS_HEAD_H
#define CPPREVIEW_NETS_HEAD_H

namespace nets {

void tcp_server();
void reuse_addr();
void buf_size();
void reuse_port();
void reuse_port_multi_process();
void select_tcp_server();


void tests() {
    {
//    tcp_server();
//    reuse_addr();
//        buf_size();

//        reuse_port();
//        reuse_port_multi_process();
    }

    select_tcp_server();
}

}

#endif //CPPREVIEW_NETS_HEAD_H
