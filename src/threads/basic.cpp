//
// Created by 阮波 on 2023/1/11.
//

#include <thread>
#include <unistd.h>
#include "comm/log.h"

void thread_func() {
    sleep(3);
    Log("thread func");
}

void stl_thread_function() {
    Log("\ncreate a new thread and run and wait for the thread run");
    {
        std::thread t(&thread_func);
        Log("main thread");

        // with join, the main thread wait for the created thread run over.
        t.join();

        Log("after thread run");
    }

    Log("\ncreate a new thread, and use 'detach' to make it a daemon process.");
    {
        std:: thread t(&thread_func);

        // after call the detach function. the thread t becomes a daemon thread.
        // and there is no connection between the std::thread object and the daemon thread.
        t.detach();

        // t.join();  // this will cause a crash.
        if(t.joinable()) {
            Log("thread t is join-able");
            t.join();
        } else {
            Log("thread t is not-join-able"); // yes
        }

        Log("after thread run");
    }
}

class ThreadFunctor {
public:
    void operator() () {
        sleep(2);
        Log("ThreadFunctor::operator()");
    }
};


void stl_thread_functor() {
    Log("\ncreate a functor(function object) and assign it to thread task");
    {
        Log("before thread create & join");

        ThreadFunctor thread_functor;
        std::thread t(thread_functor);
        t.join();

        Log("after thread join");
    }

    Log("\ncreate functor but without using temp variable");
    {
        Log("before thread create & join without temp variable");

        // TODO: why we need the add () around ThreadFactor()
        std::thread t((ThreadFunctor()));
        t.join();

        Log("after thread join");
    }
}

void stl_thread_lambda() {
    Log("\ncreate thread with lambda function");
    {
        std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;
        std::thread t(
                []() -> void {
                    Log("in thread");
                    sleep(5);
                    std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
                }
        );

        std::thread t2(
                []() -> void {
                    Log("in thread");
                    sleep(5);
                    std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
                }
        );

        t.join();
        t2.join();

        std::cout << "after t-join" << std::endl;
    }
}

void thread_func2(std::string name) {
    sleep(2);
    std::cout << "thread_func2:" << name << std::endl;
}

void thread_func3(std::string& name) {
    sleep(2);
    name = "jack";  // change the value of the reference parameter.
    std::cout << "thread_func3:" << name << std::endl;
}

void thread_func_multi_parameters(std::string& name, int& count) {
    sleep(2);
    name = "jack";
    count = 110;
    std::cout << name << "-" << count << std::endl;
}

void passing_parameter_to_thread() {
    Log("\npassing parameter to thread function");
    {
        Log("before thread-create");

        std::string name("tom");
        std::thread t(thread_func2, name);
        Log("before thread-join");
        t.join();

        Log("after thread-join");
    }

    Log("\npassing reference parameter to thread function");
    {
        std::string name("tom");

        // if we pass the name(not std::ref(name)) to the thread function, there will be a compile-time error.
        //std::thread t(thread_func3, name);

        std::thread t(thread_func3, std::ref(name));
        t.join();

        std::cout << "after thread-join, name:" << name << std::endl;  // jeck
    }

    Log("\npassing move parameter as reference to thread function");
    {
        std::string name = "tom";

        // a compile-time error too.
//        std::thread t(thread_func3, std::move(name));
//        t.join();

        std::cout << "after move parameter as reference, name:" << name << std::endl;
    }

    Log("\npassing multi parameters to thread function");
    {
        std::string name = "tom";
        int data = 1;
        std::thread t(thread_func_multi_parameters, std::ref(name), std::ref(data));
        t.join();

        std::cout << "after t-join, data:" << data << std::endl;  // 100
    }
}


void thread_copy_func() {
    sleep(2);
    Log("thread_copy_func");
}
void thread_copy_move() {
    Log("\nstd::thread object cannot be copied");
    {
        std::thread t1(thread_copy_func);
        t1.join();

        // std::thread can not be copied.
        //std::thread t2 = t1; // error: Calling a private constructor of class 'std::thread'

        Log("after t1-join");
    }

    Log("\nwe can transfer ownership of the std::thread object by std::move");
    {
        std::thread t1(thread_copy_func);
        if(t1.joinable()) {
            Log("t1 is join-able before move copy");  // yes
        } else {
            Log("t1 is not join-able after move copy");
        }

        std::thread t2 = std::move(t1);

        if(t1.joinable()) {
            Log("t1 is join-able after move copy");
        } else {
            Log("t1 is not-join-able after move copy"); // yes
        }

        t2.join();

        Log("after t2-join");
    }
}

void thread_func_3() {
    sleep(2);
    std::cout << "thread-id in thread_func_3:" << std::this_thread::get_id() << std::endl;
}

void thread_id() {
    std::cout << "main thread-id:" << std::this_thread::get_id() << std::endl;

    std::thread t(thread_func_3);

    // the id t.get_id() return is equal to the thread_func_3's std::this_thread::get_id()
    std::cout << "get std::thread object id in main thread:" << t.get_id() << std::endl;

    t.join();

    std::cout << "after t-join" << std::endl;
}


void get_thread_numbers() {
    std::cout << "thread numbers:" << std::thread::hardware_concurrency() << std::endl;
}

void basic_tests() {
//    stl_thread_function();

//    stl_thread_functor();

    stl_thread_lambda();

//    passing_parameter_to_thread();

//    thread_copy_move();

//    thread_id();

//    get_thread_numbers();
}