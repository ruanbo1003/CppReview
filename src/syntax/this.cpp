//
// Created by 阮波 on 2023/1/10.
//

#include <iostream>


class Foo {
private:
    int _val;

public:
    Foo() {
        // this-pointer is available in constructor function
        this->_val = 0;
    }
    explicit Foo(int val) {
        this->_val = val;
    }

    // this-pointer is available in destructor function
    ~Foo() {
        std::cout << this->_val << std::endl;
    }

public:
    static void fun1() {
        std::cout << "Foo::fun1()" << std::endl;
    }

    void fun2() {
        std::cout << "Foo::fun2(" << this->_val << ")" << std::endl;
    }
};

void this_pointer_test() {
    // access static through NULL pointer of class instance
    {
        Foo* f = NULL;
        f->fun1();  // Foo::fun1()
//        f->fun2();  // error
    }
}