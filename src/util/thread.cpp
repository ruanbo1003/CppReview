//
// Created by 阮波 on 2023/1/29.
//

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

namespace util::thread {
    void sleep_s(int second) {
        std::this_thread::sleep_for(std::chrono::seconds(second));
    }

    void sleep_ms(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}  // end of namespace
