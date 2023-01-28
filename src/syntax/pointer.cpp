//
// Created by 阮波 on 2023/1/9.
//
#include <iostream>


class Pointer {
private:
    int _x;
    int _y;

public:
    Pointer(): _x(0), _y(0) {
        std::cout << "Pointer()" << std::endl;
    }
    Pointer(int x, int y): _x(x), _y(y) {
        std::cout << "Pointer(" << x << "," << y << ")" << std::endl;
    }
    ~Pointer() {
        std::cout << "~Pointer()" << std::endl;
    }

public:
    void init() {
        _x = 10;
        _y = 20;
    }

    void set_x(int x) {
        this->_x = x;
    }

    int get_x() const {
        return this->_x;
    }

    void show() {
        std::cout << "{" << _x << ", " << _y << "}" << std::endl;
    }
};


void pointer_as_parameter(Pointer* p) {
    p->set_x(11);
}

void const_pointer_as_parameter(const Pointer* p) {
    // p is a const-pointer, can only call the const-member-function of class Pointer
    int x = p->get_x();
}

void class_pointer_declare_release() {
    std::cout << "declare a pointer variable and the new function to initialize the variable" << std::endl;
    {
        Pointer* p = new Pointer();
        p->init();
        p->show();

        delete p;  // use delete to release the pointer. or it will cause memory leak.
    }
}

void point_parameter_test() {
    std::cout << "Pointer as function parameter and update the class pointer value";
    {
        Pointer* p = new Pointer();
        p->init();
        p->show();  // {10, 20}

        pointer_as_parameter(p);
        p->show(); // {11, 20}

        delete p;
    }

    std::cout << "const pointer as function parameter.";
    {
        Pointer* const p = new Pointer(10, 10);
        const_pointer_as_parameter(p);
        p->show();  // {10, 10}
        delete p;
    }
}

void say() {
    std::cout << "hello" << std::endl;
}

void good() {
    std::cout << "bye" << std::endl;
}

void function_pointer_test() {
    std::cout << "simple function pointer" << std::endl;
    {
        void (*func1)();
        func1 = say;
        func1();  // hello

        func1 = good;
        func1();  // bye

        void (*func2)() = say;
        func2();  // hello
    }

    // function pointer array
    std::cout << "\nfunction pointer array" << std::endl;
    {
        void (*funcs[2])();
        funcs[0] = say;
        funcs[1] = good;
        for(int i=0; i<2; i++) {
            funcs[i]();  // hello  bye
        }
    }

    std::cout << "\nfunction pointer array using typedef" << std::endl;
    {
        typedef void (*f_ptr)();
        f_ptr func_array[2];
        func_array[0] = say;
        func_array[1] = good;
        for(int i=0; i<2; i++) {
            func_array[i]();  // hello bye
        }
    }
}

void array_pointer_as_parameter(int* A, int len) {
    // inside the function, A is a pointer, so the sizeof(A) is 8.
    std::cout << "sizeof(A):" << sizeof(A) << std::endl;  // 8

    for(int i=0; i<len; i++) {
        std::cout << A[i] << " ";
    }  // 0 1 20
    std::cout << std::endl;
}

void array_pointer_test() {
    std::cout << "array name as array pointer to the function" << std::endl;
    {
        int array[3];  // static array
        array[0] = 0;
        array[1] = 1;
        array[2] = 20;
        array_pointer_as_parameter(array, 3);

        // declare of array, sizeof() is the allocated bytes length.
        std::cout << "sizeof(array):" << sizeof(array) << std::endl;  // 12
    }

    std::cout << "\ndynamic array" << std::endl;
    {
        int *a = new int[10];
        for(int i=0; i<10; i++) {
            a[i] = i;
        }
        for(int i=0; i<10; i++) {
            std::cout << a[i] << " ";
        }  // 0 1 2 3 4 5 6 7 8 9
        std::cout << std::endl;

        std::cout << "sizeof(a):" << sizeof(a) << std::endl;  // 8

        // release dynamic array
        delete []a;
    }

    std::cout << "\nclass pointer array" << std::endl;
    {
        Pointer* a = new Pointer[3];
        for(int i=0; i<3; i++) {
            a[i].show();  // {0, 0}
        }

        // use delete[] to release all element in dynamic array.
        delete[] a;
    }

}


void pointer_test() {
//    class_pointer_declare_release();

//    point_parameter_test();

//    function_pointer_test();

    array_pointer_test();
}

