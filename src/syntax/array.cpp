//
// Created by 阮波 on 2023/1/9.
//

#include <iostream>


class Element {
public:
    Element() {
        std::cout << "Element()" << std::endl;
    }

    ~Element() {
        std::cout << "~Element()" << std::endl;
    }

public:
    void say() {
        std::cout << "Hello" << std::endl;
    }
};


void normal_array() {
    int a[3];

    // after declare a array, the initialization value may not be zero.
    for(int i=0; i<3; i++) {
        std::cout << a[i] << " ";  // not all zero value.
    }
    std::cout << std::endl;

    // we must initialize it to make sure the value is zero
    for(int i=0; i<3; i++) {
        a[i] = 0;
    }

    // array type is class
    {
        Element a2[2];
        for (auto & each: a2) {
            each.say();  // Hello
        }

        for(int i=0; i<2; i++) {
            a2[i].say();  // Hello
        }
    }
}

void array_as_parameter(Element A[2]) {
    for(int i=0; i<2; i++) {
        A[i].say();  // Hello
    }
}

void array_pointer_as_parameter(Element* A) {
    for(int i=0; i<2; i++) {
        A[i].say();  // Hello
    }
}

void array_test() {
//    normal_array();

    {
        Element a[2];
        array_as_parameter(a);

        array_pointer_as_parameter(a);
    }

}
