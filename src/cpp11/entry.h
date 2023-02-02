//
// Created by 阮波 on 2023/1/6.
//

#ifndef CPPREVIEW_CPP11_ENTRY_H
#define CPPREVIEW_CPP11_ENTRY_H

namespace cpp11 {

#include <iostream>


void functor_test();
void variadic_template_test();
void function_bind_test();
void call_once_test();
void thread_test();
void thread_local_test();
void type_inference_test();
void type_alias_test();
void smart_pointer_test();
void memory_model_test();
void unordered_container_test();
void array_test();
void constexpr_test();
void literal_test();


void tests() {
    //    functor_test();

//    variadic_template_test();

//    function_bind_test();

//    call_once_test();

//    thread_test();

//    thread_local_test();

//    type_inference_test();

//    type_alias_test();

//    smart_pointer_test();

//    memory_model_test();

//    unordered_container_test();

//    array_test();

//    constexpr_test();

    literal_test();

    std::cout << "end of cpp11::tests()" << std::endl;
}


}



#endif //CPPREVIEW_CPP11_ENTRY_H
