//
// Created by 阮波 on 2023/1/28.
//

#include <thread>
#include "comm/log.h"


namespace cpp11 {

static std::once_flag flag_1;

static void do_once_init_func() {

    // even though every thread will run this code, but only the first thread will run the
    // callable object pass to call_once.
    std::call_once(
        flag_1,
        []() {
            Log("run only once in multiple functions");
        }
    );

    std::cout << "this thread id:%ld" << std::this_thread::get_id() << std::endl;
}

void call_once_test() {

    {
        std::thread t1(do_once_init_func);
        std::thread t2(do_once_init_func);
        std::thread t3(do_once_init_func);
        std::thread t4(do_once_init_func);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
}

}