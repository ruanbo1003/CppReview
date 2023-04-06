//
// Created by 阮波 on 2023/3/13.
//

#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <iostream>

class MyMultiThreadVector {
private:
    std::shared_mutex _mtx;
    std::vector<int> _vector;

public:
    void push(int val) {
        std::unique_lock lock_guard(_mtx);
        _vector.emplace_back(val);
    }

    size_t size() {
        std::shared_lock lock_guard(_mtx);
        return _vector.size();
    }
};

void shared_mutex_lock_test() {
    int thread_num = 10;
    MyMultiThreadVector data;
    std::vector<std::thread> threads;
    for(int i=0; i<thread_num; i++) {
        threads.emplace_back(
            std::thread([&] {
                for(int j=0; j<1000; j++) {
                    data.push(i);
                }
            }));
    }
    for(auto &each_thread: threads) {
        each_thread.join();
    }

    std::cout << data.size() << std::endl;
}