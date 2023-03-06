//
// Created by 阮波 on 2023/1/30.
//

#include <thread>
#include <atomic>
#include <cassert>
#include "comm/log.h"


namespace cpp11 {


static int x_1{0};
static int y_1{0};
static bool ready_1 = false;

static int x_2{0}, y_2{0};
static std::atomic<bool> ready_2{false};


static void mm_init_1() {
    x_1 = 1;
    y_1 = 2;
    ready_1 = true;
}

static void mm_use_1() {
    if(ready_1) {
        Log("ready(%d,%d)", x_1, y_1);
    } else {
        Log("not-ready");
    }
}

static void mm_init_2() {
    x_2 = 11;
    y_2 = 12;
    ready_2.store(true, std::memory_order_release);
}
static void mm_use_2() {
    if(ready_2.load(std::memory_order_acquire)) {
        Log("ready(%d,%d)", x_2, y_2);
    } else {
        Log("not-ready-2")
    }
}

static void write_read_global_variable() {
    Log("\nbasic type global variable write and read");
    {
        std::thread t1(mm_init_1);
        std::thread t2(mm_use_1);
        t1.join();
        t2.join();

        // when use normal basic type boolean, mm_use_1 will
        // output `not-ready' or ready(1,2)
        // other possibles like ready(0,0) not been seen. due to the
        // limited number of run times.

        Log("end of basic type write and read");
    }

    Log("\nstd::atomic variable used as condition");
    {
        std::thread t1(mm_init_2);
        std::thread t2(mm_use_2);
        t1.join();
        t2.join();

        // output of mm_use_2 is `ready(11,12)` or `not-ready-2`
        // with the use of std::atomic and std::memory_order_release and std::memory_order_acquire,
        // no other possibles like `ready(0,12)` or `ready(11,0)`

        Log("end of std::atomic");
    }
}

static void stl_memory_order_relaxed() {
    std::atomic<int> counter = {0};
    std::vector<std::thread> threads;
    for(int i=0; i<100; i++) {
        threads.emplace_back(
            [&counter]() -> void {
                for(auto i=0; i<100; i++) {
                    counter.fetch_add(1, std::memory_order_relaxed);  // the add operation is atomic
                }
            }
        );
    };
    for(auto & t : threads) {
        t.join();
    }

    Log("counter:%d", counter.load());  // always 100 * 100 = 10000
}

static void stl_memory_acquire_release() {
    std::atomic<bool> ready{false};
    int data = 0;
    std::atomic<int> var{0};

    std::thread t_sender(
        [&]() -> void {
            data = 42;
            var.store(100, std::memory_order_relaxed);

            // all operations before std::memory_order_release if this thread,
            // are visible to thread that using std::memory_order_acquire.
            ready.store(true, std::memory_order_release);
        }
    );

    std::thread t_receiver(
        [&]() -> void {
            while(!ready.load(std::memory_order_acquire)){};

            Log("data:%d, var:%d", data, var.load());  // always 42, 100
        }
    );

    t_sender.join();
    t_receiver.join();
}

static void stl_memory_order() {
//    stl_memory_order_relaxed();

    stl_memory_acquire_release();
}

void memory_model_test() {
//    write_read_global_variable();

    stl_memory_order();
}

}  // end of namespace
