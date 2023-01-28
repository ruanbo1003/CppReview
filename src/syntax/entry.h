//
// Created by 阮波 on 2023/1/6.
//

#ifndef CPPREVIEW_SYNTAX_ENTRY_H
#define CPPREVIEW_SYNTAX_ENTRY_H

#include <iostream>

void class_test();
void inherit_test();
void raii_test();
void static_tests();
void array_test();
void pointer_test();
void reference_test();
void this_pointer_test();
void template_test();
void const_test();
void noncopyable_test();
void singleton_test();


void syntax_tests() {
//    array_test();

//    class_test();

//    const_test();

//    inherit_test();

//    noncopyable_test();

//    pointer_test();

//    raii_test();

//    reference_test();

    singleton_test();

//    static_tests();

//    template_test();

//    this_pointer_test();

    std::cout << "\nend of syntax tests" << std::endl;

}

#endif //CPPREVIEW_SYNTAX_ENTRY_H
