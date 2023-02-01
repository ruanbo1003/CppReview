//
// Created by 阮波 on 2023/2/1.
//

#include <random>
#include <ctime>
#include <cstdlib>
#include "comm/log.h"


namespace cpp11 {

static int normal_get_random() {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100);
    return int(dist(rng));
}



static constexpr int constexpr_get_int() {
    return sizeof(int);
}



// error: Constexpr function never produces a constant expression.
//static constexpr int constexpr_return_random_value() {
//    // non-constexpr function 'rand' cannot be used in a constant expression.
//    return std::rand();
//}

static int normal_get_const_int() {
    return 10;
}

/*
 * a constexpr function cannot call non-constexpr-function
 */
//static constexpr int constexpr_call_non_constexpr_func() {
//    return normal_get_const_int();
//}

void constexpr_test() {
    Log("const expression");
    {
        // val_1 is a normal int, through its value is a const int 10
        int val_1 = 10;

        // val_2 is a const variable.
        // but the value of val_2 is un-known until runtime.
        // So, this is not a const expression.
        const int val_2 = normal_get_random();

        Log("val_1:%d, val_2:%d", val_1, val_2);
    }

    Log("constexpr variables");
    {
        // constexpr variable must be initialized by constant-expression.

        // constexpr int c_0;  // error: default initialization of an object of const type 'const int'
        constexpr int c_1{};

        // 10 is a const-expression
        constexpr int c_2 = 10;

        // function 'normal_get_random' is not a constexpr function.
        // so, c_3 cannot be initialized by 'normal_get_random()'
        //constexpr int c_3 = normal_get_random();  // error: Constexpr variable 'c_2' must be initialized by a constant expression.

        // function 'constexpr_get_int' is a constexpr function.
        constexpr int c_4 = constexpr_get_int();  // OK

        Log("c_1:%d, c_2:%d, c_4:%d", c_1, c_2, c_4);
    }


}

}  // end of namespace

