//
// Created by 阮波 on 2023/2/2.
//

#include "comm/log.h"


namespace cpp14 {

// this is an error in C++11.
static auto add(int x, int y) {
    return x + y;
}

template<typename T>
auto template_add(T x, T y) {
    return x + y;
}

/*
 * In the case bellow, there two return expression, and return different type, one int and one float.
 * Which is not allowed in C++14.
 *
 * If there are multiple return expressions in one function, and we want to
 * use auto to deduction the return type, the return types should be same.
 */
/*
auto multiple_return_expression_with_different_type(bool flag) {
    if(flag) {
        return 1;
    } else {
        return 1.0;
    }
}
*/

void return_type_deduction() {

    Log("basic type return value deduction.")
    {
        auto i = add(1, 2);
        Log("i:%d, type of i:%s", i, typeid(i).name());  // 3, i
    }

    Log("return value deduction of template function");
    {
        auto r1 = template_add(1, 2);
        Log("r1:%d, type of r1:%s", r1, typeid(r1).name());  // 3, i

        auto r2 = template_add(1.0, 2.0);
        Log("r2:%f, type of r2:%s", r2, typeid(r2).name()); // 3.0, f
    }


}

}  // end of namespace