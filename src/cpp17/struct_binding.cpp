//
// Created by 阮波 on 2023/7/21.
//

#include <iostream>
#include <map>
using std::cout, std::endl, std::map, std::string;


namespace cpp17 {

void struct_binding() {
    
    {
        map<int, string> m1 = {
            {1, "a"},
            {2, "world"},
        };
    
        for(auto &[k, v] : m1) {
            cout << "m[" << k << "] = " << v << endl;
        }
    }
    
    {
        int a1[2] = {1, 10};
        auto [x, y] = a1;
        cout << x << ", " << y << endl;  // 1, 10
    }
}


}  // end of namespace
