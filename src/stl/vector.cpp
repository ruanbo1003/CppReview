//
// Created by 阮波 on 2023/1/10.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "comm/log.h"


void declare_vec() {
    std::vector<int> v;
    for(int i=0; i<5; i++) {
        v.push_back(i);
    }

    for(std::vector<int>::const_iterator iter=v.cbegin(); iter!=v.cend(); iter++) {
        std::cout << *iter << " ";
    }  // 0 1 2 3 4
    std::cout << std::endl;

    for(auto each: v) {
        std::cout << each << " ";
    }  // 0 1 2 3 4
    std::cout << std::endl;

    // the vector element count
    std::cout << "size:" << v.size() << std::endl;  // 5

    // the size this vector can hold without re-allocate
    std::cout << "capacity:" << v.capacity() << std::endl;  // 8

    std::cout << "\nvector at" << std::endl;
    {
        int a1 = v.at(2);
        std::cout << "a1:" << a1 << std::endl;  // 2

        // uncaught exception: std::out_of_range
//        int a6 = v.at(6);
//        std::cout << "a6:" << a6 << std::endl;
    }

    std::cout << "\naccess vector element by index" << std::endl;
    {
        int a0 = v[0];
        std::cout << "a0:" << a0 << std::endl;  // 0

        // invalid but no exception throwed.
        int a6 = v[6];
        std::cout << "a6:" << a6 << std::endl;  // 0
    }

    std::cout << "\nvector assign" << std::endl;
    {
        std::vector<int> v1 = {10, 11, 12};
        std::vector<int> v2 = {0, 1, 2, 3, 4, 5};
        v2.assign(v1.begin(), v1.end());

        std::cout << "v1:";
        for(auto each: v1) {
            std::cout << each << " ";
        }  // 10 11 12
        std::cout << std::endl;

        std::cout << "v2:";
        for(auto each: v2) {
            std::cout << each << " ";
        }  // 10 11 12
        std::cout << std::endl;
    }

    std::cout << "\nvector clear" << std::endl;
    {
        std::vector<int> v1 = {1, 2, 3};
        v1.clear();
        log_vec(v1, "v1");
    }

    std::cout << "\nvector empty" << std::endl;
    {
        std::vector<int> v = {1, 2};
        std::cout << "v.empty():" << v.empty() << std::endl;  // 0

        v.clear();
        std::cout << "v.empty():" << v.empty() << std::endl;  // 1
    }

    std::cout <<"\nvector reverse" << std::endl;
    {
        std::vector<int> v = {1, 2, 3};
        std::reverse(v.begin(), v.end());

        log_vec(v, "v");  // 3 2 1
    }

    std::cout << "\nvector pop_back" << std::endl;
    {
        std::vector<int> v = {1, 2, 3};
        v.pop_back();
        log_vec(v, "v");  // 1, 2
    }

    std::cout << "\nvector all_of, any_of" << std::endl;
    {
        std::vector<int> v = {1, 2, 3};
//        std::cout << "v.all_of(1):" << std::all_of(v.begin(), v.end(), 1) << std::endl;
//        std::cout << "v.any_of(2):" << std::any_of(v.begin(), v.end(), 2) << std::endl;
    }
}

class VecElem {
private:
    int _data;

public:
    VecElem(): _data(0) {
        Log("VecElem()");
    }
    VecElem(int data): _data(data) {
        std::cout << "VecElem(" << data << ")" << std::endl;
    }
    VecElem(const VecElem& rhs) : _data(rhs._data) {
        std::cout << "VecElem(const VecElem& rhs)" << std::endl;
    }
    VecElem& operator=(const VecElem& other) {
        this->_data = other._data;
        return *this;
    }
    ~VecElem() {
        std::cout << "~VecElem()" << std::endl;
    }

public:
    int get_data() const {
        return _data;
    }
    void set_data(int data) {
        _data = data;
    }
};

void add_element_to_vector() {

    std::cout << "\ncreate a new object and use push_back to add it to vector" << std::endl;
    {
        std::vector<VecElem> v;
        VecElem elem;

        std::cout << "before push_back" << std::endl;

        // when use push_back to add an existed object to std::vector, it will call the copy-constructor to
        // create a new object and then add it to the std::vector
        v.push_back(elem);  // VecElem(const VecElem& rhs)

        std::cout << "after push_back" << std::endl;
        // ~VecElem(); ~VecElem();
    }

    std::cout << "\ncreate a new object and use emplace_back to add it to vector" << std::endl;
    {
        std::vector<VecElem> v;
        VecElem elem;

        std::cout << "before emplace_back" << std::endl;

        // when emplace_back an existed object to std::vector, it is the same as push_back.
        v.emplace_back(elem);  // VecElem(const VecElem& rhs)

        std::cout << "after emplace_back" << std::endl;
        // ~VecElem(); ~VecElem();
    }

    std::cout << "\ncreate new object in push_back's parameter" << std::endl;
    {
        std::vector<VecElem> v;

        // the parameter VecElem() create a new object, then inside the push_back,
        // call the copy-constructor to create another new object and add it to the std::vector.
        v.push_back(VecElem());  // VecElem(); VecElem(const VecElem& rhs);
        // ~VecElem(); ~VecElem();
    }

    std::cout << "\ncreate object in emplace_back's parameter" << std::endl;
    {
        std::vector<VecElem> v;

        // the same as above.
        v.emplace_back(VecElem());  // VecElem(); VecElem(const VecElem& rhs);
        // ~VecElem(); ~VecElem();
    }

    std::cout << "\nadd new object with constructor parameter to vector" << std::endl;
    {
        // If we want to create a new object with parameters and add it to the std::vector.
        // We can also use push_back or emplace_back.
        // But there are different between the two ways.

        std::cout << "use push_back" << std::endl;
        {
            std::vector<VecElem> v;

            // When use push_back, the push_back's parameter can not be the type of the std::vector we defined.
            // So we create a new object and then call the push_back function to add the new object to the std::vector.
            // And then inside the push_back function, create a new object use copy-constructor and add it to the vector.
            VecElem elem(10);  // VecElem(10);

            v.push_back(elem);  // VecElem(const VecElem& rhs);
            // ~VecElem(); ~VecElem();
        }

        std::cout << "use emplace_back" << std::endl;
        {
            std::vector<VecElem> v;

            // Different with push_back, when we use emplace_back, we can pass the element constructor's parameters to
            // the emplace_back function, do not need to create a new object first.
            // The emplace_back create a new object and add it to the std::vector.
            // Only one constructor and one destructor called, which is half compared with push_back.
            v.emplace_back(10);  // VecElem(10);
            // ~VecElem();
        }
    }

}


void vector_test() {
//    declare_vec();

    add_element_to_vector();
}