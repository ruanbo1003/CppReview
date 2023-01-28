//
// Created by 阮波 on 2023/1/6.
//

#include <iostream>
#include "comm/log.h"


void constructor_destructor_function();
void class_parameters();


void class_test() {
//    constructor_destructor_function();

    class_parameters();

    Log("end of class tests");
}

class Point {
private:
    int count;

public:
    explicit Point(int count) {
        this->count = count;
        std::cout << "Point(" << this->count << ")" << std::endl;
    }
    Point() {
        count = 0;
        std::cout << "Point()" << std::endl;
    }

    // copy constructor
    Point(const Point& other) {
        this->count = other.count;
        std::cout << "Point(const Point& other)(" << this->count << ")" << std::endl;
    }

    // assign constructor
    Point& operator = (const Point& rhs) {
        this->count = rhs.count;
        std::cout << "Point operator = (const Point& rhs)(" << this->count << ")" << std::endl;
        return *this;
    }

    ~Point() {
        std::cout << "~Point(" << this->count << ")" << std::endl;
    }

public:
    void show() const {
        std::cout << "Point::show(), count:" << this->count << std::endl;
    }

    void update(int count) {
        this->count = count;
    }
};

void constructor_destructor_function() {
    Log("\ndefault constructor with not parameter");
    {
        Point p1;
        p1.show();

        Point* pp1 = new Point();
        pp1->show();
        delete pp1;
    }


    Log("\ndefault constructor with parameter");
    {
        Point p2(10);
        p2.show();

        Point *pp2 = new Point(20);
        pp2->show();
        delete pp2;
    }

    Log("\ncopy constructor");
    {
        Point p1(1);

        Point p2 = p1;
        p2.update(200);
    }

    Log("\nassign constructor");
    {
        Point p1(10);
        Point p2(20);

        p2 = p1;  // assign constructor
    }


    Log("\n\n");
}

// function parameter is a class instance.
// when call this function and pass a class instance to the function.
// the class copy-constructor will be called to generator the class instance parameter.
void class_as_parameter(Point p) {
    p.show();
}

// function return a class instance.
// By default, the compiler will optimize the two constructor calls.
// The optimization called RVO(return value optimize).
// The RVO can be disabled by add -fno-elide-constructors to the compiler flags.
Point return_a_class() {
    Point p(100);  // default constructor with parameter
    return p;
}


// function parameter is a class reference.
// the parameter p is a reference and no extra constructor will be called.
// If the class reference value not changed in the function, we can use a const reference.
void class_reference_as_parameter(Point& p) {
    p.show();
}

// function parameter is a class pointer.
// No extra constructor will be called.
void class_pointer_as_parameter(Point* p) {
    p->show();
}


void class_parameters() {
    Log("\nfunction parameter is a class instance");
    {
        Point p1(1);
        class_as_parameter(p1);
    }

    Log("\nfunction parameter is a class reference");
    {
        Point p1(1);
        class_reference_as_parameter(p1);
    }

    Log("\nfunction parameter is a class pointer");
    {
        Point* pp = new Point(1);
        class_pointer_as_parameter(pp);
        delete pp;
    }

    Log("\nfunction return a class instance");
    {
        Point p = return_a_class();  // copy-constructor (RVO compiler flag: -fno-elide-constructors )
        p.update(2);
    }
}


// rule-of-three:
// if a class need a non-default destructor function. it's also need the copy-constructor and the assign-operator function.
class RuleOfThree {
public:
    RuleOfThree(){
    }

    RuleOfThree(const RuleOfThree& rhs){
    }
    RuleOfThree& operator=(const RuleOfThree& other) {
        return *this;
    }

    ~RuleOfThree() {

    }
};

