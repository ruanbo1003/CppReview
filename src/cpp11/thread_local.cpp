//
// Created by 阮波 on 2023/2/1.
//

#include <thread>
#include <mutex>
#include "comm/log.h"


namespace cpp11 {

static void multiple_thread_add_local_int_variable() {
    // when a variable declared as thread_local, each thread will
    // own this variable by itself, not shared by other threads.
    thread_local int counter = 0;
    std::mutex mtx;

    std::thread ta([&](){
        for(int i=0; i<100; i++) {
            counter += 1;
        }

        std::lock_guard<std::mutex> lock(mtx);
        Log("thread a counter:%d", counter);  // always 100
    });

    std::thread tb([&]() {
        for(int i=0; i<1000; i++) {
            counter += 1;
        }

        std::lock_guard<std::mutex> lock(mtx);
        Log("thread b counter:%d", counter);  // always 1000
    });

    std::thread tc([&]() {
        for(int i=0; i<10000; i++) {
            counter += 1;
        }

        std::lock_guard<std::mutex> lock(mtx);
        Log("thread c counter:%d", counter);  // always 10000
    });

    ta.join();
    tb.join();
    tc.join();

    for(int i=0; i<10; i++) {
        counter += 1;
    }
    Log("main thread counter:%d", counter);  // always 10
}

void thread_local_test() {
    multiple_thread_add_local_int_variable();
}

}  // end of namespace
