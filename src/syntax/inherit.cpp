//
// Created by 阮波 on 2023/1/7.
//

#include "comm/log.h"


class Fruit {
public:
    Fruit() {
        Log("Fruit()");
    }
    virtual ~Fruit() {
        Log("~Fruit()");
    }

public:
    virtual void color() {
        Log("Fruit::color()");
    }
};

class Apple : public Fruit {
public:
    Apple() : Fruit() {
        Log("Apple()");
    }
    ~Apple() {
        Log("~Apple()");
    }

public:
    void color() {
        Log("Apple::color()");
    }
};


class Animal {
public:
    Animal() {
        Log("Animal()");
    }
    ~Animal() {
        Log("~Animal()");
    }

public:
    void cry() {
        Log("Animal::cry()");
    }

};

class Dog : public Animal {
public:
    Dog() : Animal() {
        Log("Dog()");
    }
    ~Dog() {
        Log("~Dog()");
    }

public:
    void cry() {
        Log("Dog::cry(), wang-wang");
    }
};

class Cat : public Animal {
public:
    Cat() : Animal() {
        Log("Cat()");
    }
    ~Cat() {
        Log("~Cat()");
    }

public:
    void cry() {
        Log("Cat::cry(), mie-mie");
    }
};

class VirtualFunctionBase {
public:
    virtual void say() {
        Log("Base::say()");
    }
};

class VirtualFunctionDriver : public VirtualFunctionBase {
public:
    void say() {
        Log("Driver::say()");
    }
};

void inherit_test() {
    // Base class without virtual destructor
    Log("\nBase class without virtual destructor");
    {
        // constructor & destructor order
        // base constructor -> driver constructor -> driver destructor -> base destructor
        Dog dog;
        dog.cry();
    }

    Log("\nbase class without virtual function and base pointer to driver class instance");
    {
        Dog dog;
        Animal* animal = &dog;
        dog.cry();  // Dog::cry()
        animal->cry();  // Animal::cry()
    }

    Log("\nbase class with virtual destructor function and base pointer to driver class");
    {
        VirtualFunctionDriver driver;
        VirtualFunctionBase* p_base = &driver;

        driver.say();  // Driver::say()
        p_base->say();  // Driver::say()
    }

    Log("\nbase class without virtual destructor and base pointer to new driver instance");
    {
        // constructor and destructor call order
        // base constructor -> driver constructor -> base destructor
        // the driver destructor not been called, which is not right.
        Animal* p_base = new Cat();
        p_base->cry();  // Animal::cry()
        delete p_base;
    }

    Log("\nbase class with virtual destructor and base pointer the new driver instance");
    {
        // constructor and destructor call order
        // Fruit() -> Apple() -> ~Apple() -> ~Fruit()
        // which is the correct order.
        Fruit* p_base = new Apple();
        p_base->color();
        delete p_base;
    }

}