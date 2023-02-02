//
// Created by 阮波 on 2023/2/2.
//

#include "comm/log.h"


namespace cpp14 {

void separator_test() {
    // i1 and i2 have the same value.
    int i1 = 10000000;
    int i2 = 10'000'000;  // single quotes (')
    Log("i1:%d, i2:%d", i1, i2);

    // f1 and f2 have the same value.
    float f1 = 10000.0;
    float f2 = 10'000.0;  // single quotes (')
    Log("f1:%f, f2:%f", f1, f2);
}

}  // end of namespace