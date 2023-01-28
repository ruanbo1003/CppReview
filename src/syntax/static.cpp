//
// Created by 阮波 on 2023/1/8.
//

#include <iostream>


void static_variable_in_function();
void static_class_member_test();


void static_tests() {
    for(int i=0; i<5; i++) {
        static_variable_in_function(); // 1, 2, 3, 4, 5
    }

    static_class_member_test();
}


void static_variable_in_function() {
    // call the function many times.
    // only the first time will initialize the counter to 0, and others will not
    static int counter = 0;

    counter++;

    std::cout << "counter:" << counter << std::endl;
}



class Counter {
private:
    // _num is a normal variable, each class instance has its own _num variable.
    int _num;

    // all class instance share this _counter variable.
    static int _counter;

public:
    Counter() {
        _num = 100;
    }

public:
    static void add() {
        _counter++;
//        _num++;  // can not access normal class variable in static class method.
    }

    void num_add() {
        _num++;
        _counter++;
    }

    void normal_func() {
        _num++;
        _counter++;  // can access static class variable in normal(non-static) class method.
    }

    void show() {
        std::cout << "counter:" << _counter << ", number:" << _num << std::endl;
    }
};

int Counter::_counter = 100;

void static_class_member_test() {
    Counter counter1;
    counter1.add();
    counter1.num_add();
    counter1.show();  // counter: 101, number: 101

    counter1.add();
    counter1.num_add();
    counter1.show();  // counter: 102, number: 102

    Counter counter2;
    counter2.add();
    counter2.num_add();
    counter2.show();  // counter: 103, number: 101

    Counter counter3;
    counter3.show();  // counter: 103, number: 100
}