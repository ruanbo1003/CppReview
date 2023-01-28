//
// Created by 阮波 on 2023/1/12.
//

/*
 *  variadic template 可变模板参数
 *  https://www.cnblogs.com/qicosmos/p/4325949.html
 */

#include <iostream>
#include "comm/log.h"


namespace cpp11 {

    template<typename T>
    T t_add(const T &arg) {
        return arg;
    }

    template<typename T, typename... ARGS>
    T t_add(const T &arg, const ARGS &... args) {

        Log("sizeof t_add ARGS:%lu", sizeof...(ARGS));

        return arg + t_add(args...);
    }

    template<typename... ARGS>
    auto fold_add(const ARGS &... args) {
        Log("sizeof fold_add ARGS:%lu", sizeof...(ARGS));

        return (args + ...);
    }

    void t_add_test() {
        auto sum = t_add(1, 2u, 3u, 4u);
        std::cout << "sum:" << sum << std::endl;

        auto sum2 = fold_add(1, 2u, 3u, 4u);
        Log("sum2:%d", sum2);
    }


    void variadic_template_test() {
        t_add_test();
    }

}  // end of namespace