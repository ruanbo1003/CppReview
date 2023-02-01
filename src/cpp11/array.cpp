//
// Created by 阮波 on 2023/2/1.
//
#include <array>
#include <algorithm>
#include "comm/log.h"


namespace cpp11 {

void array_test() {
    Log("declare and initialize array");
    {
        // declare and initialize each element
        std::array<int, 5> a1 = {1, 2, 3, 4, 5};
        for(auto &each: a1) {
            LogLine("%d ", each);
        }  // 1, 2, 3, 4, 5
        Log("\n");

        std::array<int, 5> a2;
        for(auto & each : a2) {
            LogLine("%d ", each);
        }  // undefined integer value
        Log("\n");

        // specify the first element, and the others will be
        // initialized by default zero value(0)
        std::array<int, 5> a3 = {1};
        for(auto & each : a3) {
            LogLine("%d ", each);
        }  // 1 0 0 0 0
        Log("\n");

        std::array<int, 5> a4;
        a4.fill(1);
        std::for_each(
        a4.begin(), a4.end(), [](auto it){ LogLine("%d ", it);}
        );  // 1 1 1 1 1
        Log("\n");
    }

    Log("deduce the size of the array");
    {
        std::array<int, 5> a1;
        std::array a2 = {1, 2, 3, 4, 5};
        std::array a3 = {1, 2, 3};

        // 5 5 3
        Log("size of a1:%ld, a2:%ld, a3:%ld", a1.size(), a2.size(), a3.size());  // 5 5 3

        // NSt3__15arrayIiLm5EEE NSt3__15arrayIiLm5EEE NSt3__15arrayIiLm3EEE
        Log("type of a1:%s, a2:%s, a3:%s", typeid(a1).name(), typeid(a2).name(), typeid(a3).name());
    }

    Log("access array element");
    {
        std::array<int, 5> a = {1, 2, 3, 4, 5};

        int i1 = a[1];  // access array element by index
        int i2 = a.at(1);  // use at
        int i3 = std::get<1>(a);  // use std::get

        // 2 2 2
        Log("i1:%d, i2:%d, i3:%d", i1, i2, i3);
    }

    Log("array of array");
    {
        std::array<std::array<int, 3>, 3> mat = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9,
        };
        for(auto & a : mat) {
            for(auto & each : a) {
                LogLine("%d ", each);
            }
            Log("");
        }
    }

    Log("sort array");
    {
        std::array a = {1, 2, 3, 9, 8, 7, 5, 4, 6, 0};
        std::sort(a.begin(), a.end());
        std::for_each(
        a.begin(), a.end(), [](auto each) -> void { LogLine("%d ", each); }
        );  // 0 1 2 3 4 5 6 7 8 9
        Log("");

        std::sort(a.begin(), a.end(), [](auto a, auto b) -> bool {return a > b;});
        for(auto & each: a) {
            LogLine("%d ", each);
        }  // 9 8 7 6 5 4 3 2 1
        Log("");
    }
}

}  // end of namespace
