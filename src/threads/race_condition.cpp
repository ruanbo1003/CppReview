//
// Created by 阮波 on 2023/1/12.
//

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>


class Wallet {
private:
    int _money;

public:
    Wallet() : _money(0) {}

public:
    int get_money() {
        return _money;
    }

    void add_money(int count) {
        for(int i=0; i<count; i++) {
            this->_money++;
        }
    }
};

void multi_thread_change_one_variable() {
    Wallet wallet;
    std::vector<std::thread> threads;

    for(int i=0; i<5; i++) {
        threads.push_back(std::thread(&Wallet::add_money, &wallet, 10000));
    }
//    for(auto &t: threads) {
//        t.join();
//    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    // total money is not equal to 50000, why?
    // the money add operator: this->_money++; is not a atomic operation.
    // Actually, it has three commands:
    // 1. Load variable(this->_money) to register.
    // 2. Increment register value by 1.
    // 3. Update variable(this->_money) with register's value.
    // When we create multiple threads to add money(the this->_money++ operation), each thread do the three command alone.
    // The situation bellow could happen:
    // this->_money's value is 1.
    // threat-1 load value to register, the register's value is 1.
    // thread-1 add register's value by 1 to 2.
    // thread-2 load value to register, the register's value is 1.
    // thread-2 add register's value by 1 to 2.
    // thread-1 update this->_money value with register's value, now this->_money's value is 2.
    // thread-2 update this->_money value with register's value, not this->_money's value is 2.

    // See what happened, the variable's value is 1, after two thread do the add operation,
    // the variable's value is 2, not 3.

    std::cout << "total money:" << wallet.get_money() << std::endl;
}


static int counter = 0;
void thread_func_add() {
    for(int i=0; i<10000; i++) {
        counter += 1;
    }
}
void write_a_race_condition() {
    std::vector<std::thread> threads;
    for(int i=0; i<5; i++) {
        threads.push_back(std::thread(thread_func_add));
    }
    for(auto &each: threads) {
        each.join();
    }

    std::cout << "counter after join:" << counter << std::endl;
}

void race_condition_tests() {
//    multi_thread_change_one_variable();

    write_a_race_condition();
}