//
// Created by 阮波 on 2023/3/16.
//

#ifndef CPPREVIEW_HEAD_H
#define CPPREVIEW_HEAD_H

namespace ipc {

void shm_write();
void shm_read();


void tests() {

    shm_write();

    shm_read();
}

}  // end of namespace

#endif //CPPREVIEW_HEAD_H
