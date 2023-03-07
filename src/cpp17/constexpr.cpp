//
// Created by 阮波 on 2023/3/6.
//
#include "comm/log.h"


namespace cpp17 {

static void if_constexpr();
static void lambda_constexpr();


void constexpr_test() {
//    if_constexpr();

    lambda_constexpr();

}

template<bool ok>
constexpr void is_ok() {
    if constexpr(ok == true) {
        Log("ok");
    } else {
        Log("not-ok");
    }
}

static void if_constexpr() {
    is_ok<true>(); // ok

    is_ok<false>(); // not-ok
}

static void lambda_constexpr() {
    constexpr auto l1 = [](int n) {return  n * n; };
    cout << l1(2) << endl;  // 4
    cout << l1(3) << endl;  // 9
}


}
