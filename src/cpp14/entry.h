//
// Created by 阮波 on 2023/2/2.
//

#ifndef CPPREVIEW_CPP14_ENTRY_H
#define CPPREVIEW_CPP14_ENTRY_H

#include "comm/log.h"


namespace cpp14 {

void return_type_deduction();
void lambda_test();
void template_test();
void separator_test();


void tests() {
//    return_type_deduction();

//    lambda_test();

//    template_test();

    separator_test();

    Log("\nend of C++ 14 tests");
}

}  // end of namespace


#endif //CPPREVIEW_CPP14_ENTRY_H
