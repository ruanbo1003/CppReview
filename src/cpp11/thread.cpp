//
// Created by 阮波 on 2023/1/29.
//
#include <chrono>
#include <functional>
#include <thread>
#include <vector>
#include "comm/log.h"
#include "util/util.h"


namespace cpp11 {

void create_vector_of_threads();

void thread_test() {
    Log("\ncreate vector of multiple threads");
    {
        create_vector_of_threads();
    }

}


void create_vector_of_threads() {
    std::function<void()> thread_fun = []() {
        std::cout << "thread id:" << std::this_thread::get_id() << std::endl;

        util::thread::sleep_s(1);
    };

    Log("create two std::thread objects and push_back to std::vector. Notice that we must use the std::move");
    {
        auto start_time = std::chrono::system_clock::now();

        std::vector<std::thread> threads;

        std::thread t1(thread_fun);
        std::thread t2(thread_fun);

        threads.push_back(std::move(t1));
        threads.push_back(std::move(t2));

        for(std::thread & t : threads) {
            if(t.joinable()) {
                t.join();
            }
        }

        auto end_time = std::chrono::system_clock::now();
        std::chrono::duration<double,std::milli> time_cost = end_time - start_time;

        Log("after threads join, time cost: %fms", time_cost.count());
    }

    Log("\npush_back std::thread instance to std::vector without temporary std::thread object");
    {
        auto start_time = std::chrono::system_clock::now();

        std::vector<std::thread> threads;
        threads.emplace_back(std::thread(thread_fun));
        threads.emplace_back(std::thread(thread_fun));
        threads.emplace_back(std::thread(thread_fun));

        for(auto & t : threads) {
            if(t.joinable()) {
                t.join();
            }
        }

        Log("after threads join");

        auto end_time = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> time_cost = end_time - start_time;
    }

    Log("\nstd::thread object is only movable, not copyable, not assignable");
    {
        std::thread t1;
        // std::thread t2(t1);  //error: Calling a private constructor of class 'std::thread'
        //std::thread t3;
        //t3 = t1;  // error: 'operation=' is a private member of 'std::thread'
    }


}

}  // end of namespace