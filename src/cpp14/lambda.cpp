//
// Created by 阮波 on 2023/2/2.
//

#include "comm/log.h"


namespace cpp14 {

void lambda_test() {
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

}  // end of namespace
