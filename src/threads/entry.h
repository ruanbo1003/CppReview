//
// Created by 阮波 on 2023/1/11.
//

#ifndef CPPREVIEW_THREADS_ENTRY_H
#define CPPREVIEW_THREADS_ENTRY_H

#include <iostream>


void basic_tests();
void race_condition_tests();
void mutex_tests();
void condition_variable_tests();
void shared_mutex_lock_test();


void thread_tests() {
//    basic_tests();

//    race_condition_tests();

//    mutex_tests();

//    condition_variable_tests();

    shared_mutex_lock_test();

    std::cout << "\nend of thread tests" << std::endl;
}

#endif //CPPREVIEW_THREADS_ENTRY_H
