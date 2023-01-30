//
// Created by 阮波 on 2023/1/12.
//

#include <iostream>
#include <mutex>


class Singleton1 {
private:
    int _data;

    // private static pointer that point to the Singleton class object.
    static Singleton1* _instance;

    /*
     *  we make all the constructors private so that instance of the Singleton class can not be
     *  created outside of the class.
     */
    // Default constructor is private but need to be implemented.
    // Because the new operator need to call this constructor function in the get_instance() function.
    Singleton1(){
    }

    // Copy constructor and assign operator do not need to be implemented.
    // Because there is no copy or assign operation to the instance.
    Singleton1(const Singleton1& rhs);
    Singleton1& operator=(const Singleton1& other);

public:
    int get_data() const {
        return this->_data;
    }

    void add() {
        this->_data++;
    }

    // public static method that returns the pointer to the Singleton class object.
    static Singleton1* get_instance() {
        if(not _instance) {
            // There is no instance of the class

            _instance = new Singleton1();  // create a instance
            _instance->_data = 0;
        }

        return _instance;
    }
};
// initialize instance will NULL
Singleton1* Singleton1::_instance = NULL;

class Singleton2 {
private:
    int _data;
    static Singleton2* _instance;

private:
    Singleton2() : _data(0) {
        std::cout << "Singleton2()" << std::endl;
    }

public:
    Singleton2(const Singleton2& rhs) = delete;
    Singleton2& operator=(const Singleton2& other) = delete;

    static Singleton2* get_instance() {
        return _instance;
    }

    void add() {
        this->_data += 1;
    }
    int get_data() const {
        return this->_data;
    }
};

Singleton2* Singleton2::_instance = new Singleton2();


class ThreadSafeSingleton {
private:
    int _data;
    static ThreadSafeSingleton* _instance;
    static std::mutex _mutex;

    ThreadSafeSingleton(): _data(0) {
        std::cout << "ThreadSafeSingleton()" << std::endl;
    }

public:
    ThreadSafeSingleton(const ThreadSafeSingleton& rhs) = delete;
    ThreadSafeSingleton& operator = (const ThreadSafeSingleton& other) = delete;

    static ThreadSafeSingleton* get_instance() {
        std::lock_guard<std::mutex> lock(_mutex);
        if(not _instance) {
            _instance = new ThreadSafeSingleton();
        }
        return _instance;
    }

    int get_data() const {
        return this->_data;
    }
    void add() {
        this->_data += 1;
    }
};
ThreadSafeSingleton* ThreadSafeSingleton::_instance = NULL;
std::mutex ThreadSafeSingleton::_mutex;


void singleton_test() {

    std::cout << "declare singleton class use static member" << std::endl;
    {
        std::cout << "get instance first time" << std::endl;
        {
            // We cannot create an instance of the Singleton class as all constructors are private.
            // We have to use the get_instance() method to get an instance of the Singleton class.
            Singleton1* singleton = Singleton1::get_instance();
            singleton->add();
            std::cout << "data:" << singleton->get_data() << std::endl;
        }
        std::cout << "get instance second time" << std::endl;
        {
            Singleton1* singleton = Singleton1::get_instance();
            singleton->add();
            std::cout << "data:" << singleton->get_data() << std::endl;
        }
    }

    std::cout << "\ninitialize the static instance pointer with new Singleton2()" << std::endl;
    {
        std::cout << "get instance first time" << std::endl;
        {
            Singleton2* singleton = Singleton2::get_instance();
            singleton->add();
            std::cout << "data:" << singleton->get_data() << std::endl;  // 1
        }

        std::cout << "get instance second time" << std::endl;
        {
            Singleton2* singleton = Singleton2::get_instance();
            singleton->add();
            std::cout << "data:" << singleton->get_data() << std::endl;  // 2
        }
    }

    std::cout << "\nthread safe singleton" << std::endl;
    {
        std::cout << "first instance" << std::endl;
        {
            ThreadSafeSingleton* singleton = ThreadSafeSingleton::get_instance();
            singleton->add();
            std::cout << "data:" << singleton->get_data() << std::endl;  // 1
        }

        std::cout << "second instance" << std::endl;
        {
            ThreadSafeSingleton* singleton = ThreadSafeSingleton::get_instance();
            singleton->add();
            std::cout << "data:" << singleton->get_data() << std::endl;  // 2
        }
    }
}