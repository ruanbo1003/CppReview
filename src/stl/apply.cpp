//
// Created by 阮波 on 2023/3/7.
//
#include "comm/log.h"

/*
 * apply: since c++17
 */

namespace stl {

static int add(int a, int b) {
    return a + b;
}

void apply_test() {
    {
        pair p(1, 2);
        //add(p);  // error: no matching function for call to 'add'
    }

    // use apply to pass pair to function as multiple parameters.
    {
        pair p(1, 2);
        auto sum = apply(add, p);
        cout << "sum:" << sum << endl;  // 3
    }

    // use apply to pass tuple to function(lambda) as multiple parameters.
    {
        auto add = [](auto first, auto second) { return first + second; };
        auto sum = apply(add, tuple(1, 2));
        cout << "sum:" << sum;  // 3
    }
}

}