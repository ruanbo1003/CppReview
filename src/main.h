//
// Created by 阮波 on 2023/1/6.
//

#ifndef CPPREVIEW_MAIN_H
#define CPPREVIEW_MAIN_H

#include "cpp11/entry.h"
#include "cpp14/entry.h"

#include "syntax/entry.h"
#include "stl/entry.h"
#include "lambda/entry.h"
#include "threads/entry.h"
#include "codeanalysis/entry.h"


void entry() {
//    code_analysis::tests();

    // modern C++
    {
//        cpp11::tests();
        cpp14::tests();
    }


//    lambda_test();

//    stl_tests();

//    syntax_tests();

//    thread_tests();
}

#endif //CPPREVIEW_MAIN_H
