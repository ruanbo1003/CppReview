//
// Created by 阮波 on 2023/1/28.
//

#include <functional>
#include "comm/log.h"

/*
 * std::bind is used to take a function(or a function object or anything you can to invoke using the (...) syntax)
 * and produce a function object with one or more arguments fo the argument function `bound` or rearranged.
 *
 * std::function is a type that can hold a value of just about anything you can to invoke using the (...) syntax.
 * In particular, the result of stt::bind ban be assigned to a std::function.
 */

namespace cpp11 {

void example_from_cpp_reference();

void function_bind_test() {
    example_from_cpp_reference();

}


// https://en.cppreference.com/w/cpp/utility/functional/function
struct Foo {
    int _num;

    Foo(int num): _num(num) {}

    void print_add(int i) const {
        Log("Foo::print_add:%d", _num + i);
    }
};

void print_num(int i) {
    Log("print_num:%d", i);
}

struct PrintNum {
    void operator()(int i) const {
        Log("PrintNum():%d", i);
    }
};

void example_from_cpp_reference() {
    Log("store a normal function");
    {
        std::function<void(int)> f_1 = print_num;
        f_1(-9);  // print_num:-9
    }

    Log("\nstore a lambda");
    {
        std::function<void()> f_2 = []() { print_num(42); };
        f_2();  // print_num:42
    }

    Log("\nstore the result of std::bind");
    {
        std::function<void()> f_3 = std::bind(print_num, 100);
        f_3();  // print_num:100
    }

    Log("\nstore the call to member function");
    {
        std::function<void(const Foo& foo, int)> f_4 = &Foo::print_add;
        const Foo foo(11);
        f_4(foo, 100);  // Foo::print_add:111
        f_4(foo, 200); // Foo::print_add:211
        f_4(300, 1);  // Foo::print_add:301
    }

    Log("\nstore the call to data member accessor");
    {
        std::function<int(Foo const&)> f_num = &Foo::_num;
        const Foo foo(102);
        Log("f_num:%d", f_num(foo));  // 102
    }

    Log("\nstore to call a member function and object");
    {
        Foo foo(100);
        std::function<void(int)> f = std::bind(&Foo::print_add, foo, std::placeholders::_1);
        f(2);  // 102
        f(11);  // 111
    }

    Log("\nstore call to a member function and object pointer");
    {
        Foo foo(200);
        std::function<void(int)> f = std::bind(&Foo::print_add, &foo, std::placeholders::_1);
        f(1);  // 201
        f(11);  // 202
    }

    Log("\nstore to call a function object");
    {
        std::function<void(int)> f = PrintNum();
        f(20);  // PrintNum():20
        f(30);  // PrintNum():30
    }

    Log("\nfactorial");
    {
        auto factorial = [](int n) {
            std::function<int(int)> fac = [&](int n) {return (n<2)? 1: n*fac(n-1); };
            return fac(n);
        };

        for(int i{1}; i!=8; i++) {
            Log("%d! = %d", i, factorial(i));
        }
    }
}

} // end of namespace