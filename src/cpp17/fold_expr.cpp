//
// Created by 阮波 on 2023/3/7.
//
#include "comm/log.h"


namespace cpp17 {

template<typename ... T>
static auto sum(T...t) {
    return (t + ...);
}

void fold_expr_test() {
    {
        int a = sum(1, 2);
        cout << a << endl;  // 3

        a = sum(1, 2, 3);
        cout << a << endl;  // 6

        cout << sum(1, 2, 3, 4) << endl;  // 10
    }
}

}  // end of namespaces
