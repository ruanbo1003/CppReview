//
// Created by 阮波 on 2023/3/6.
//
#include "comm/log.h"


namespace cpp17 {

struct RetItem {
    double d;
    int i;
};
static RetItem get_item() {
    double d = 1.0;
    int i = 10;

    // return {d, i}, not a RetItem instance.
    return {d, i};
}
static RetItem get_item_2() {
    return {2.0, 20};
}

void structure_binding_test() {
    auto [d, i] = get_item();
    Log("d:%f, i:%d", d, i);  // 1.0, 10

    auto [d2, i2] = get_item_2();
    Log("d2:%f, i2:%d", d2, i2);  // 2.0, 20

}

}  // end of namespace
