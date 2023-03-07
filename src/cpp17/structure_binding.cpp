//
// Created by 阮波 on 2023/3/6.
//
#include <map>
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
    // return value bind
    {
        auto [d, i] = get_item();
        Log("d:%f, i:%d", d, i);  // 1.0, 10

        auto [d2, i2] = get_item_2();
        Log("d2:%f, i2:%d", d2, i2);  // 2.0, 20
    }

    // iterate over map
    {
        map<int, string> m = {
                {1, "c++"},
                {2, "java"},
                {3, "python"},
        };
        for(const auto & [id, lang] : m) {
            cout << id << ":" << lang << endl;
        }
    }

    // update value
    {
        pair a(1, 2.0);
        auto& [i, d] = a;
        i = 10;
        cout << a.first << endl;  // 10
    }

}

}  // end of namespace
