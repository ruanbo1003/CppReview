//
// Created by 阮波 on 2023/1/10.
//

#include <iostream>
#include <string>


// function template.
// we call the function directly.
// the system will inference the type for us.
template<class T>
T add(T x, T y) {
    return x + y;
}

template<typename T>
T add2(T x, T y) {
    return x + y;
}


// when make instance of the template class.
// we must specify the template type.
template<class T>
class TemplateClass {
private:
    T _data;

public:
    TemplateClass() {
        std::cout << "TemplateClass()" << std::endl;
//        _data = T(0);
    }

    TemplateClass(T data) {
        std::cout << "TemplateClass(" << data << ")" << std::endl;
        _data = data;
    }

public:
    void show() {
        std::cout << "TemplateClass data:" << _data << std::endl;
    }
};


void template_test() {

    std::cout << "normal template function" << std::endl;
    {
        int x=1, y=20;
        int z = add(1, y);
        std::cout << "z:" << z << std::endl;

        int z2 = add2(x, y);
        std::cout << "z2:" << z2 << std::endl;

        std::string hi = add(std::string("Hello"), std::string("World"));
        std::cout << "hi:" << hi << std::endl;  // HelloWorld
    }

    std::cout << "\ntemplate class" << std::endl;
    {
        TemplateClass<int> c1;
        c1.show();

        TemplateClass<std::string> c2;
        c2.show();

        TemplateClass<std::string> c3("hello");
        c3.show();  // hello
    }
}
