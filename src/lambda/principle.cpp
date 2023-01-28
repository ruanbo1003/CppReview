//
// Created by 阮波 on 2023/1/11.
//

#include <iostream>


class print_class {
public:
    void operator() (void) const {
        std::cout << "hello lambda" << std::endl;
    }
};

void lambda_principle() {
    // the compiler will transform the lambda to a lambda object.
    // just like the two implementation

    auto print1 = []() -> void { std::cout << "hello lambda" << std::endl; };
    print1();  // hello lambda

    print_class print2;
    print2();  // hello lambda
}