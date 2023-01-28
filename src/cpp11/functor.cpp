//
// Created by 阮波 on 2023/1/11.
//

/*
 * A function object, or functor, is any type that implements operator().
 * This operator is referred to as the call operator or sometimes the application operator.
 * The C++ Standard Library uses function objects primarily as sorting criteria for containers and in algorithms.
 *
 * Function objects provide two main advantages over a straight function call.
 * The first is that a function object can contain state.
 * The second is that a function object is a type and therefore can be used as s template parameter.
 *
 * From: https://learn.microsoft.com/en-us/cpp/standard-library/function-objects-in-the-stl?view=msvc-170
 */


#include <iostream>

namespace cpp11 {

    class AddFunctor {
    public:
        int operator()(int a, int b) {
            return a + b;
        }
    };

    class AddFunctorWithCounter {
    private:
        int _count;

    public:
        AddFunctorWithCounter() : _count(0) {
        }

        // the factor function-class must override the () operator.
        int operator()(int a, int b) {
            this->_count += 1;
            return a + b;
        }

        int get_add_count() const {
            return _count;
        }
    };


    void functor_test() {

        std::cout << "normal function object." << std::endl;
        {
            AddFunctor add;
            int i = 1, j = 100;
            int sum = add(i, j);
            std::cout << "sum:" << sum << std::endl;  // 101

            int sum2 = add(1, 20);
            std::cout << "sum2:" << sum2 << std::endl; // 21
        }

        std::cout << "function object, support object state" << std::endl;
        {
            AddFunctorWithCounter add;

            int i = 1, j = 100;
            int sum1 = add(i, j);
            std::cout << "sum1:" << sum1 << std::endl; // 101

            int sum2 = add(1, 20);
            std::cout << "sum2:" << sum2 << std::endl; // 21

            int add_count = add.get_add_count();
            std::cout << "add count:" << add_count << std::endl; // 2
        }
    }

}  // end of namespace
