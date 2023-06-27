    //
// Created by 阮波 on 2023/6/27.
//

#include <iostream>

using std::cout, std::endl;


namespace cpp11 {

class Array {
private:
    int _size;
    int* _ptr;
    
public:
    Array() {
        cout << "default constructor" << endl;
        
        _size = 0;
        _ptr = nullptr;
    }
    
    explicit Array(int size) {
        _size = size;
        _ptr = new int[_size] { 0 };
    }
    
    // assign operator; Array a2; a2 = a1;
    Array& operator=(const Array& rhs) {
        cout << "assign operator" << endl;
        
        if(this == &rhs) {
            return *this;
        }
        
        if(_ptr) {
            delete [] _ptr;
        }
        
        _size = rhs._size;
        _ptr = new int[_size];
        for(auto i=0; i<_size; i++) {
            _ptr[i] = rhs._ptr[i];
        }
        
        return *this;
    }
    
    // move assignment
    Array& operator = (Array&& rhs) noexcept {
        cout << "move assignment" << endl;

        _size = rhs._size;
        _ptr = rhs._ptr;
        rhs._ptr = nullptr;

        return *this;
    }
    
    // copy constructor;
    // Array a2(a1);
    // Array a2 = a1;
    Array(const Array& rhs) {
        cout << "Copy Constructor(size=" << rhs._size << ")" << endl;
        
        _size = rhs._size;
        _ptr = new int[_size];
        for(auto i=0; i<_size; i++) {
            _ptr[i] = rhs._ptr[i];
        }
    }
    
    // move constructor
    Array(Array&& rhs) noexcept {
        cout << "move constructor(size=" << rhs._size << ")" << endl;
        this->_size = rhs._size;
        this->_ptr = rhs._ptr;  // transform the ownership

        rhs._size = 0;
        rhs._ptr = nullptr;
    }
    
    ~Array() {
        if(_ptr) {
            delete [] _ptr;
            _ptr = nullptr;
        }
    }
    
    void init() {
        for(auto i=0; i<_size; i++) {
            _ptr[i] = i * i;
        }
    }
    
    friend std::ostream& operator << (std::ostream& os, const Array& array) {
        std::cout << "Array[";
        for(int i=0; i<array._size; i++) {
            std::cout << array._ptr[i];
            if(i < array._size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        
        return os;
    }
    
    // add `+` operator
    Array operator + (const Array& rhs) {
        Array sum(_size + rhs._size);
        
        for(int i=0; i<this->_size; i++) {
            sum._ptr[i] = this->_ptr[i];
        }
        for(int i=0; i<rhs._size; i++) {
            sum._ptr[this->_size+i] = rhs._ptr[i];
        }
        
        return sum;
    }
    
    int& operator[](int i) {
        return _ptr[i];
    }
    
    int length() const {
        return _size;
    }
};


void why_move() {
    Array a1 = Array(3);
    a1.init();
    std::cout << a1 << std::endl;
    
    cout << "===== default constructor ====" << endl;
    {
        Array a2(2);
        std::cout << a2 << endl;
    }
    
    cout << "===== copy constructor ==== " << endl;
    {
        Array a2(a1);
        cout << a2 << endl;
        
        Array a3 = a1;
        cout << a3 << endl;
    }
    
    cout << "====== assignment operator =====" << endl;
    {
        Array a2;
        a2 = a1;
        cout << a2 << endl;
    }
    
    cout << endl << "===== add `+` operator =====" << endl;
    {
        Array a2(4);
        a2.init();
        
        // if the `move constructor` not implemented, this will call the copy constructor, which will
        // copy the data from that return by the `+` operator.
        Array sum = a1 + a2;
        
        cout << sum << endl;
    }
    
    cout << endl << "===== move assignment =====" << endl;
    {
        Array a2(5);
        a2.init();
        
        Array sum;
        sum = a1 + a2;
//        cout << sum << endl;
    }
}


}  // end of namespace
