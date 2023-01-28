//
// Created by 阮波 on 2023/1/12.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


class WalletMutex {
private:
    int _money;
    std::mutex _mutex;

public:
    WalletMutex() : _money(0) {
    }

public:
    int get_money() const {
        return this->_money;
    }

    void add_money(int money) {
        _mutex.lock();

        std::cout << "add_money:" << this << std::endl;

        for(int i=0; i<money; i++) {
            this->_money += 1;
        }

        _mutex.unlock();
    }

    void add_money_with_lock_guard(int count) {
        // lock_guard: a class template, which implements the RAII for mutex.
        std::lock_guard<std::mutex> lock_guard(_mutex);

        std::cout << "add_money_with_lock_guard:" << this << std::endl;

        for(int i=0; i<count; i++) {
            this->_money += 1;
        }
    }
};


void mutex_tests() {
    std::cout << "\nfix race condition by std::mutex" << std::endl;
    {
        WalletMutex wallet;

        std::vector<std::thread> threads;
        threads.reserve(5);

        for(int i=0; i<5; i++) {
//            threads.emplace_back(std::thread(&WalletMutex::add_money, &wallet, 10000));

            threads.emplace_back(&WalletMutex::add_money, &wallet, 10000);
        }
        for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

        std::cout << "total money:" << wallet.get_money() << std::endl;
    }

    std::cout << "std::lock_guard" << std::endl;
    {
        WalletMutex wallet;
        std::vector<std::thread> threads;

        for(int i=0; i<5; i++) {
            threads.emplace_back(&WalletMutex::add_money_with_lock_guard, &wallet, 10000);
        }
        std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

        std::cout << "std::lock_guard total money:" << wallet.get_money() << std::endl;
    }
}