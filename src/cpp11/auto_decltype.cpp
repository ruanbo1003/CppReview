//
// Created by 阮波 on 2023/1/29.
//

#include <typeinfo>
#include <vector>
#include "comm/log.h"


namespace cpp11 {

static void auto_test() {

    Log("\ndeclare variables with auto");
    {
        auto x = 1;
        auto y = 2.0;
        auto px = &x;
        auto py = &y;

        Log("type of x:%s", typeid(x).name());  // i, stand for integer
        Log("type of px:%s", typeid(px).name()); // Pi, stand for pointer of integer
        Log("type of y:%s", typeid(y).name());  // d, stand for double
        Log("type of py:%s", typeid(py).name()); // Pd, stand for pointer of double

        Log("type of 1:%s", typeid(1).name());  // i

        Log("type of hello:%s", typeid("hello").name());  // A6_c
        Log("type of hell:%s", typeid("hell").name());  // A5_c
    }

    Log("\nuse auto to avoid long type name");
    {
        std::vector<int> v{1, 2, 3, 4, 5, 6};

        // before c++11, we must declare it with long type name.
        for(std::vector<int>::iterator it=v.begin(); it!=v.end(); it++) {
            LogLine("%d ", *it);
        }
        Log("");

        // after c++11, we can use auto to deduction the type of it.
        for(auto it=v.begin(); it!=v.end(); it++) {
            LogLine("%d ", *it);
        }
        Log("");

        // even, we can use range-based for loop
        for(auto &each : v) {
            LogLine("%d ", each);
        }
        Log("");
    }
}

static int decltype_return_integer() {
    return 1;
}

static char decltype_return_char() {
    return 'a';
}

template<typename T>
static T decltype_return_template() {
    return T{};
}

static void decltype_test() {
    Log("\ndecltype type from basic type variable");
    {
        int i1 = 1;
        auto i2 = 1;
        decltype(i1) i_1;
        decltype(i2) i_2;
        Log("type of i1:%s, i_1:%s", typeid(i1).name(), typeid(i_1).name());  // i, i
        Log("type of i2:%s, i_2:%s", typeid(i2).name(), typeid(i_2).name());  // i, i
    }

    Log("\ndecltype type from return type of function");
    {
        decltype(decltype_return_integer()) i;
        Log("type of i:%s", typeid(i).name());  // i

        decltype(decltype_return_char()) c;
        Log("type of c:%s", typeid(c).name());  // c
    }

    Log("\ndecltype type from return type of template function");
    {
        decltype(decltype_return_template<int>()) i;
        Log("type of i:%s", typeid(i).name());  // i

        decltype(decltype_return_template<char>()) c;
        Log("type of c:%s", typeid(c).name());  // c

        decltype(decltype_return_template<float>()) f;
        Log("type of f:%s", typeid(f).name());  // f
    }

    Log("what's the output of decltype(expression)");
    {
        decltype(10) i;
        Log("type of i:%s", typeid(i).name());

        // cannot output decltype(10)
        // error: expected '(' for function-style case of type construction
        //std::cout << decltype(10) << std::endl;
    }
}

template<class T1, class T2>
static auto find_max_1(T1 a, T2 b) {
    return a > b ? a : b;
}

template<class T1, class T2>
static auto find_max_2(T1 a, T2 b) -> decltype(a > b ? a : b) {
    return a > b ? a : b;
}

static void auto_and_decltype_test() {
    Log("auto return with out decltype");
    {
        auto m1 = find_max_1(1, 2.0);
        auto m2 = find_max_1(1.0, 2);

        Log("m1:%f, m2:%f", m1, m2);
        Log("type of m1:%s, m2:%s", typeid(m1).name(), typeid(m2).name());  // d, d
    }

    Log("auto return and specify return type with decltype");
    {
        auto m1 = find_max_2(1, 2.0);
        auto m2 = find_max_2(1.0, 2);

        Log("m1:%f, m2:%f", m1, m2);
        Log("type of m1:%s, m2:%s", typeid(m1).name(), typeid(m2).name());  // d, d
    }
}

void type_inference_test() {
//    auto_test();

//    decltype_test();

    auto_and_decltype_test();
}

}  // end of namespace