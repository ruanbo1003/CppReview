//
// Created by 阮波 on 2023/3/29.
//
#include "comm/log.h"

namespace rvalue {

/*
 * lvalue: locator value, (identity, movable)
 * rvalue: read value, (movable expression)
 *
 * xvalue: expiring value, (identity, non-movable)
 * glvalue: generalized lvalue, (lvalue + xvalue, identity)
 * pvalue: pure rvalue,  (non-identity, movable)
 *
 *
 * lvalue:
 *  1. use '&' to get address
 *  2. can be used to initialize rvalue reference
 *  3. durable object after the expression
 *
 * rvalue:
 *  1. temporary object that non-exists after the expression
 *
 */

void rvalue_reference() {
    Log("lvalue reference");
    {
        int i = 1;
        int &lr = i;

        // int &lr2 = 10;  // error
    }

    Log("rvalue reference");
    {
        int && rr = 10;  // ok
        int *p = &rr;
        Log("*p:%d", *p);  // 10
        
        *p = 100;
        Log("*p:%d", *p);  // 100
    }
    
}

}  // end of namespace
