//
// Created by 阮波 on 2023/3/16.
//
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>


namespace ipc {

void shm_read() {
    key_t key = ftok("ipc_shm_file", 65);
    int shm_id = shmget(key, 1024, 0666|IPC_CREAT);
    if(shm_id == -1) {
        std::cout << "read shmget failed" << std::endl;
        return;
    }
    char *str = (char*) shmat(shm_id, NULL, 0);
    if(shmdt(str) == -1) {
        std::cout << "read shmat failed" << std::endl;
        return;
    }

    shmctl(shm_id, IPC_RMID, nullptr);

    std::cout << "read from shm:" << str << std::endl;
}

}  // end of namespace
