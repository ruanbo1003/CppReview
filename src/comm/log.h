//
// Created by 阮波 on 2023/1/6.
//

#ifndef CPPREVIEW_COMM_LOG_H
#define CPPREVIEW_COMM_LOG_H

#include <iostream>
#include <string>


//void Log(const char *str);

#define Log(...) { std::printf(__VA_ARGS__); std::printf("\n"); }
#define LogLine(...) { std::printf(__VA_ARGS__); }


template<class T>
void log_vec(const std::vector<T>& vec, const char* name) {
    std::cout << name << ":";
    for(auto &each : vec) {
        std::cout << each << " ";
    }
    std::cout << std::endl;
}

#endif
