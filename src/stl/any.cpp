//
// Created by 阮波 on 2023/3/6.
//

#include <any>
#include "comm/log.h"

/*
 * any: since c++ 17
 */

namespace stl {

void any_test() {
    // any type
    {
        std::any a1 = 1;
        cout << a1.type().name() << ":" << std::any_cast<int>(a1) << endl;  // i:1

        std::any a2 = 3.14;
        cout << a2.type().name() << ":" << std::any_cast<double>(a2) << endl;  // d:3.14

        std::any a3 = true;
        cout << a3.type().name() << ":" << std::any_cast<bool>(a3) << endl;  // b:1
    }

    // has value, reset
    {
        std::any a = 10;
        if(a.has_value()) {
            cout << "has value" << endl;
        }

        a.reset();
        if(a.has_value()) {
            cout << "has value" << endl;
        } else {
            // no-value
            cout << "no-value" << endl;
        }
    }

    // invalid any_cast
    {
        std::any a = 10;
        try {
            auto val = std::any_cast<float>(a);
        }
        catch (const std::bad_any_cast& e) {
            // error:bad any cast
            cout << "error:" << e.what() << endl;
        }
    }

    {
        std::any a = vector<int>{1, 2, 3};
        cout << a.type().name() << endl;
    }
}


}  // end of namespace
