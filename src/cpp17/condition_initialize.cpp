//
// Created by 阮波 on 2023/3/6.
//
#include "comm/log.h"
#include <map>

namespace cpp17 {

void condition_initialize_test() {

    // if condition initialize
    {
        std::map<int, int> m = {
                {1, 1},
        };
        if(auto res=m.insert(std::make_pair(2, 2)); res.second) {
            // inserted
            Log("inserted");
        } else {
            Log("not-inserted");
        }

        if(auto r=m.insert(std::make_pair(2,2)); r.second) {
            Log("inserted");
        } else {
            // not-inserted
            Log("not-inserted");
        }
    }

    // switch condition initialize
    {
        // initialize val in switch condition expression
        switch (int val=10; val) {
            case 1:
                Log("val is one");
                break;
            case 2:
                Log("val is two");
                break;
            default:
                Log("not one or two");
                break;
        }
    }
}

}