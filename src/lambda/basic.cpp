//
// Created by 阮波 on 2023/1/11.
//

#include <algorithm>
#include <iostream>


void abs_sort(int* x, unsigned int n) {
    std::sort(
            x,
            x+n,
            // lambda expression begin
            [](int a, int b) {
                return (std::abs(a) < std::abs(b));
            }
            // lambda expression end
    );
}

void basic_test() {
    std::cout << "function use basic lambda expression" << std::endl;
    {
        int a[] = {5, -4, 3, 10, -9};
        abs_sort(a, 5);

        for(auto each: a) {
            std::cout << each << " ";
        }  // 3 -4 5 -9 10
    }
}