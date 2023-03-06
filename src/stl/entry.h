//
// Created by 阮波 on 2023/1/10.
//

#ifndef CPPREVIEW_STL_ENTRY_H
#define CPPREVIEW_STL_ENTRY_H

#include <iostream>

namespace stl {

void vector_test();
void list_test();
void map_test();
void any_test();


void stl_tests() {
//    vector_test();

//    list_test();

//        map_test();

    any_test();

    std::cout << "\nend of stl tests" << std::endl;
    }
}

#endif //CPPREVIEW_STL_ENTRY_H
