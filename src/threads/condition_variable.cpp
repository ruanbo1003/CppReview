//
// Created by 阮波 on 2023/1/12.
//

#include <iostream>
#include <condition_variable>
#include <random>
#include <thread>
#include <unistd.h>
#include <functional>

/*
 * std::condition_variable
 * https://en.cppreference.com/w/cpp/thread/condition_variable
 */


class CondValApp {
private:
    int _count;

    std::condition_variable _cond_var;
    std::mutex _mutex;

public:
    CondValApp() : _count(0) {
        std::cout << "Task()" << std::endl;
    }
    ~CondValApp() {
        std::cout << "~Task()" << std::endl;
    }

public:
    [[noreturn]]
    void produce() {
        std::cout << "produce thread " << std::this_thread::get_id() << " begin" << std::endl;

        for(;;) {
            int second = rand() % 3 + 1;
            sleep(second);

            std::lock_guard<std::mutex> guard(_mutex);
            _count++;

            std::cout << "produce one" << std::endl;
            _cond_var.notify_one();
        }

    }

    [[noreturn]]
    void consumer() {
        std::cout << "consumer thread " << std::this_thread::get_id() << " begin" << std::endl;

        while (true)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _cond_var.wait(lock);

            std::cout << "thread " << std::this_thread::get_id() << " consumed" << std::endl;
        }
    }
};


/*
 * https://en.cppreference.com/w/cpp/thread/condition_variable
 */
void condition_variable_tests()
{
    srand((unsigned)time(NULL));

    std::cout << "on produce thread, two consumer thread" << std::endl;

    CondValApp app;
    std::thread produce_t(&CondValApp::produce, &app);
    std::vector<std::thread> consumers;
    for(int i=0; i<2; i++) {
        consumers.emplace_back(&CondValApp::consumer, &app);
    }

    produce_t.join();
    std::for_each(consumers.begin(), consumers.end(), std::mem_fn(&std::thread::join));

    std::cout << "end of joins" << std::endl;
}
