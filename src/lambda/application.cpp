//
// Created by 阮波 on 2023/1/11.
//

#include <iostream>


void stl_for_each() {
    int a[4] = {1, 4, 3, 2};
    std::for_each(
            a,
            a+4,
            [=](int x){ std::cout << x << " "; }
    );  // 1, 4, 3, 2
    std::cout << std::endl;

    std::sort(
            a,
            a+4,
            [=](int x, int y) -> bool { return x < y; }
    );
    std::for_each(
            a,
            a+4,
            [=](int x) { std::cout << x << " "; }
    );  // 1 2 3 4
    std::cout << std::endl;
}


void lambda_application() {
    stl_for_each();
}
