//
// Created by 阮波 on 2023/3/6.
//

#ifndef CPPREVIEW_CPP17_ENTRY_H
#define CPPREVIEW_CPP17_ENTRY_H

#include "comm/log.h"

namespace cpp17 {

void constexpr_test();
void structure_binding_test();
void condition_initialize_test();
void namespace_test();
void fold_expr_test();
void file_system_test();


void tests() {
//    constexpr_test();

//    structure_binding_test();

//    condition_initialize_test();

//    namespace_test();

//    fold_expr_test();

    file_system_test();

    Log("end of c++ 17 test");
}

}



#endif //CPPREVIEW_CPP17_ENTRY_H
