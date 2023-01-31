//
// Created by 阮波 on 2023/1/31.
//

#include "comm/log.h"


namespace code_analysis {

void memory_problem_test() {
    int *array = new int[10];
    delete [] array;

    Log("array[1]:", array[1]);
}

} // end of namespace
