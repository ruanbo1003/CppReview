//
// Created by 阮波 on 2023/3/7.
//

#include "comm/log.h"
#include <optional>

/*
 *  optional: since c++ 17
 */

namespace stl {

optional<string> get_str(bool ok) {
    if(ok) {
        return "hello";
    } else {
        return {};
    }
}

auto get_str2(bool ok) {
    return ok ? optional<string>{"hello"} : nullopt;
}

void optional_test() {
    {
        optional<string> r1 = get_str(true);
        cout << r1.value_or("empty") << endl;  // hello

        optional<string> r2 = get_str(false);
        cout << r2.value_or("empty") << endl;  // empty
    }

    {
        auto r1 = get_str2(true);
        cout << r1.value_or("empty") << endl;  // hello
        cout << *r1 << endl;  // hello

        auto r2 = get_str2(false);
        cout << r2.value_or("empty") << endl;  // empty
        cout << *r2 << endl;  // nullptr
    }
}


}