//
// Created by 阮波 on 2023/2/2.
//

#include "comm/log.h"
#include <iostream>


namespace cpp14 {

template<class T>
constexpr T PI = T(3.141592653589L);

static void variable_template() {
    Log("PI<int>:%d", PI<int>);  // 3
    Log("PI<float>:%f", PI<float>);  // 3.141593
}

template<typename T, typename U>
struct TemplateAliasTest
{
    T _data_1;
    U _data_2;

    TemplateAliasTest(T data_1, U data_2): _data_1(data_1), _data_2(data_2) {
    }

    void display() {
        std::cout << "_data_1:" << _data_1 << ", type:" << typeid(_data_1).name() << std::endl;
        std::cout << "_data_2:" << _data_2 << ", type:" << typeid(_data_2).name() << std::endl;
    }
};

// alias and specify one template
template<typename U>
using IntTemplateAliasTest = TemplateAliasTest<int, U>;

// alias and specify two template
using IntFloatTemplateAliasTest = TemplateAliasTest<int, float>;

static void template_alias() {
    auto t1 = TemplateAliasTest<int, double>(1, 2.0);
    t1.display();  // 1, i; 2 d

    auto t2 = IntTemplateAliasTest<double>(1, 2.0);
    t2.display();  // 1, i; 2, d

    auto t3 = IntFloatTemplateAliasTest(1, 2.0);
    t3.display();  // 1, i; 1 f
}


void template_test() {
//    variable_template();

    template_alias();
}

}  // end of namespace
