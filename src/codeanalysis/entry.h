//
// Created by 阮波 on 2023/1/31.
//

#ifndef CPPREVIEW_CODEANALYSIS_ENTRY_H
#define CPPREVIEW_CODEANALYSIS_ENTRY_H

#include "comm/log.h"

namespace code_analysis {

void memory_problem_test();
void core_dump_test();


void tests() {
    Log("code analysis examples begin \n")

//    memory_problem_test();

    core_dump_test();
}

}  // end of namespace


#endif //CPPREVIEW_CODEANALYSIS_ENTRY_H
