//
// Created by 阮波 on 2023/2/2.
//

#include "comm/log.h"


namespace cpp14 {

static void generic_lambda_use_auto() {
    Log("lambda in C++ 11");
    {
        // in C++11, the parameter of the lambda expression must be specified.
        auto func = [](int a) {return a;};
        auto i1 = func(1);
        auto i2 = func(2.1);

        // 1, i, 2, i
        Log("i1:%d, type i1:%s, i2:%d, type i2:%s", i1, typeid(i1).name(), i2, typeid(i2).name());
    }

    Log("lambda in C++ 14");
    {
        // in C++14, we can use auto to deduct the type of the lambda.
        auto func = [](auto a) {return a;};
        auto i1 = func(1);
        auto i2 = func(2.1);

        // i, 1, 2.1, f
        Log("i1:%d, type i1:%s, i2:%f, type i2:%s", i1, typeid(i1).name(), i2, typeid(i2).name());
    }
}

static void lambda_init_capture_list() {
    auto f1 = [](int x, int y) -> int { return x + y; };
    auto v1 = f1(1, 2);
    auto v2 = f1(10, 2);
    Log("v1:%d, v2:%d", v1, v2);  // 3, 12

    auto f2 = [x = 1](int y) -> int { return x + y; };
    auto v3 = f2(1);
    auto v4 = f2(10);
    Log("v3:%d, v4:%d", v3, v4);  // 2, 11

    auto generator_int = [x = 0]() mutable -> int { return x++; };
    auto i1 = generator_int();
    auto i2 = generator_int();
    auto i3 = generator_int();
    auto i4 = generator_int();
    Log("i1:%d, i2:%d, i3:%d, i4:%d", i1, i2, i3, i4);  // 0, 1, 2, 3

    Log("we passing only-movable value to lambda expression by use of capture initialization");
    {
        auto p = std::make_unique<int>(1);
        Log("p:%d", *p);  // 1

        // error: Call to implicitly-deleted copy constructor of 'std::make_unique<>'
        // auto f1 = [p]() -> void { Log("%d", *p); };

        auto f2 = [&p]() -> void { Log("%d", *p); };
        f2();  // 1

        auto f3 = [ptr = std::move(p)]() -> void { Log("%d", *ptr); };
        f3();  // 1

        if(p) {
            Log("p is not empty");
        } else {
            // empty
            Log("p is empty")
        }
    }
}

void lambda_test() {
//    generic_lambda_use_auto();

    lambda_init_capture_list();

}

}  // end of namespace
