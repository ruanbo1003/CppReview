//
// Created by 阮波 on 2023/1/10.
//

#include <iostream>

void const_variable() {
    std::cout << "normal variable can change value whenever you want" << std::endl;
    {
        int i = 0;
        i = 10;
        std::cout << "i:" << i << std::endl;
    }

    std::cout << "\nconst variable cannot change the value after initialize" << std::endl;
    {
        const int i = 0;
//        i = 10;  // error: Cannot assign to variable 'i' with const-qualified type 'const int'
    }

    std::cout << "\nbut we can change a const variable through a pointer" << std::endl;
    {
        const int i = 0;
        int* p = (int*)&i;
        *p = 10;

        // the const only keep the variable non-changeable in compile-time.
        std::cout << i << ", " << *p << std::endl;  // 0, 10
    }
}


void const_pointer() {

    std::cout << "const before the type" << std::endl;
    {
        char hello[] = "hello";
        char world[] = "world";

        // the value which the pointer point to is const, cannot change by the pointer.
        const char* p1 = hello;
        p1 = world;
//        p1[0] = 'z';  // error: read-only variable is not assignable

        std::cout << "p:" << p1 << std::endl;  // world
    }

    std::cout << "\nconst after the type pointer" << std::endl;
    {
        char hello[] = "hello";
        char world[] = "world";

        // the pointer(p) is const, cannot change the pointer value.
        char* const p = hello;
//        p = world;  // error: cannot assign variable 'p' with const-qualified type with 'char *cont'

        p[0] = 'H';
        std::cout << "p:" << p << std::endl;  // Hello
    }
}

class Item {
private:
    int _data;
    const int _val;  // the const member variable must be explicit initialized in constructor function.

public:
    Item(): _data(0), _val(10) {
        std::cout << "Item()" << std::endl;
    }
    Item(int data): _data(data), _val(10) {
        std::cout << "Item(" << _data << ")" << std::endl;
    }
    Item(const Item& rhs) : _val(10) {
        _data = rhs._data;
    }
    Item& operator=(const Item& other) {
        this->_data = other._data;
        return *this;
    }
    ~Item() {
        std::cout << "~Item()" << std::endl;
    }

public:
    int get_data() const {
//        _data = 10;  // error: Cannot assign to non-static data member within const member function.
        return _data;
    }
};

void const_in_class() {
    Item item;
    int data = item.get_data();
    std::cout << "data:" << data << std::endl;
}

void reference_parameter(int& i) {
    i = 100;
}

void const_reference_parameter(const int& i) {
//    i = 100;  // error: Cannot assign to variable 'i' with const-qualified 'const int&'
}

void const_parameter() {
    std::cout << "\nreference parameter can change value if the function" << std::endl;
    {
        int i = 0;
        reference_parameter(i);
        std::cout << "i:" << i << std::endl;  // 100
    }

    std::cout << "\nconst reference parameter cannot change value in the function" << std::endl;
    {
        int i = 0;
        const_reference_parameter(i);
        std::cout << "i:" << i << std::endl;  // 0
    }
}


void const_test() {
//    const_variable();

//    const_pointer();

//    const_in_class();

    const_parameter();

    std::cout << "\nend of const test" << std::endl;
}