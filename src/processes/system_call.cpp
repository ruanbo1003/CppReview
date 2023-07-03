//
// Created by 阮波 on 2023/6/30.
//
#include <unistd.h>  // getpid()
#include <sys/syscall.h>
#include <iostream>

using std::cout, std::endl;


namespace processes {

void call_by_libc_func() {
    pid_t pid = getpid();
    cout << "pid:" << pid << endl;

}

void call_by_system_call() {
    pid_t pid = syscall(SYS_getpid);
    cout << "pid:" << pid << endl;
}

void system_call() {
    call_by_libc_func();

    call_by_system_call();

}


}  // end of namespace
