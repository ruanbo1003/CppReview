//
// Created by 阮波 on 2023/1/9.
//

#include <iostream>


void reference_declare_initialize() {
    std::cout << "normal reference declare and initialize" << std::endl;
    {
        int i = 10;
        int& ri = i;  // the reference must be initialized to another same type variable.
        std::cout << i << ", " << ri << std::endl;  // 10, 10

        ri = 20;
        std::cout << i << ", " << ri << std::endl;  // 20, 20

        int j = 3;
        ri = j;
        std::cout << j << ", " << ri << std::endl;
    }

    std::cout << "\nconst reference" << std::endl;
    {
        int i = 10;
        const int &ri = i;
        std::cout << i << ", " << ri << std::endl;  // 10, 10

        i = 20;
        std::cout << i << ", " << ri << std::endl;  // 20, 20

        int j = 2;
        // const reference can not re-assign to another variable.
        // ri = j;  // error: Cannot assign to variable 'ri' with const-qualified type 'const int &'
    }

    std::cout << "\nconst keyword after the type" << std::endl;
    {
        int i = 10;
        int const& ri = i;

        i = 20;
        std::cout << i << ", " << ri << std::endl;  // 20, 20

        // error: cannot assign to variable 'ri' with const-qualified type 'const int &'
        // ri = 30;
    }
}

void normal_type_reference_parameter(int& i) {
    // inside the function, we change the value of the reference of integer i
    i = 100;
}

void reference_parameter_test() {
    std::cout << "\nnormal type(e.g: int, float) as function parameter" << std::endl;
    {
        int i = 0;
        // the change inside the function, also change the value outside the function.
        normal_type_reference_parameter(i);
        std::cout << i << std::endl;  // 100
    }
}

void reference_test()
{
//    reference_declare_initialize();

    reference_parameter_test();
}