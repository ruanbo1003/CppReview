//
// Created by 阮波 on 2023/1/12.
//

#include <iostream>

class Noncopyable {
public:
    Noncopyable() {
        std::cout << "Noncopyable()" << std::endl;
    }
    ~Noncopyable() {
        std::cout << "~Noncopyable()" << std::endl;
    }

private:
    Noncopyable(const Noncopyable& rhs);
    Noncopyable& operator=(const Noncopyable& other);
};

class NoncopyableDriver : private Noncopyable {
};

void noncopyable_test() {
    std::cout << "\ndeclare copy-constructor and assign operator as private" << std::endl;
    {
        Noncopyable c1;
        //Noncopyable c2 = c1;  // error: Calling a private constructor of class 'Noncopyable'
        Noncopyable c3;
        // c3 = c1; // error: 'operator =' is private member of 'Noncopyable'
    }

    std::cout << "Noncopyable driver class also non-copyable" << std::endl;
    {
        NoncopyableDriver c1;

        // copy constructor os NoncopyableDriver is implicitly deleted because base class
        // Noncopyable has an inaccessible copy constructor.
        //NoncopyableDriver c2 = c1; // error: Call to implicitly-deleted copy constructor of 'NoncopyableDriver'

        NoncopyableDriver c3;
        // c3 = c1; // error: Object of type 'NoncopyableDriver' cannot be assigned because its copy assignment operator is implicitly deleted.
    }
}