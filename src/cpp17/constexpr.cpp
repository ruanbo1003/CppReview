//
// Created by 阮波 on 2023/3/6.
//
#include "comm/log.h"


namespace cpp17 {

static void if_constexpr();

void constexpr_test() {
    if_constexpr();

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


}
