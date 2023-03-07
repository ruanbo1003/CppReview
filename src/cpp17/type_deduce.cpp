//
// Created by 阮波 on 2023/3/7.
//

#include "comm/log.h"

/*
 * constructor type deduce.
 */

namespace cpp17 {


void type_deduce() {

    pair<int, double> p1(1, 2.0);  // before c++17
    pair p2(1, 2.0);  // since c++17

    vector<int> v1 = {1, 2, 3,};  // before c++17
    vector v2 = {1, 2, 3};  // since c++17

}

}  // end of namespace
