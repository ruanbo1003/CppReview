//
// Created by 阮波 on 2023/1/29.
//

#include "comm/log.h"


namespace cpp11 {

static int alias_func_1(int a, int b) {
    Log("%d + %d = %d", a, b, a+b);
    return a + b;
}

static void basic_alias() {
    Log("\nalias of basic data type");
    {
        // in case of basic type, using alias and typedef alias has the same effect.
        using long_alias = long;
        typedef long long_alias_2;

        long_alias l1{1};
        long_alias_2 l2{2};

        Log("l1:%ld, l2:%ld", l1, l2); // 1, 2
    }

    Log("alias of function pointer");
    {
        using f_ptr = int(*)(int, int);  // using is much more readable the typedef.
        typedef int(*f_ptr_2)(int, int);

        f_ptr f1 = &alias_func_1;
        f_ptr_2 f2 = &alias_func_1;

        auto sum1 = f1(1, 2);  // 1 + 2 = 3
        Log("sum1:%d", sum1); // 3

        auto sum2 = f2(10, 20);  // 10 + 20 = 30
        Log("sum2:%d", sum2);  // 30
    }

}

// when use with template, using cannot be replaced by typedef.
template<typename T> using ptr = T*;

static void using_alias_with_template() {

    // template cannot be declared in function.
    //template<typename T> using p = T*;  // error:
    ptr<int> p1;
    ptr<double> p2;
    ptr<char> p3;

    // Pi, Pd, Pc
    Log("type of p1:%s, p2:%s, p3:%s", typeid(p1).name(), typeid(p2).name(), typeid(p3).name());
}

void type_alias_test() {
//    basic_alias();

    using_alias_with_template();

}

}

