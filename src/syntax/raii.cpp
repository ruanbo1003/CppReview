//
// Created by 阮波 on 2023/1/7.
//

/*
 * RAII: Resource Acquisition Is Initialization
 */

#include <iostream>
#include <pthread.h>


class Mutex {
private:
    pthread_mutex_t _mutex;

public:
    Mutex() {
        pthread_mutex_init(&_mutex, nullptr);
    }
    ~Mutex() {
        pthread_mutex_destroy(&_mutex);
    }

    // disable copying & assign
    Mutex(const Mutex&) = delete;
    void operator = (const Mutex&) = delete;

public:
    void Lock() {
        pthread_mutex_lock(&_mutex);
    }

    void Unlock() {
        pthread_mutex_unlock(&_mutex);
    }
};

class MutexRaii {
private:
    Mutex* _mutex;

public:
    explicit MutexRaii(Mutex *mutex) : _mutex(mutex) {
        this->_mutex->Lock();
    }
    ~MutexRaii() {
        this->_mutex->Unlock();
    };

    // No copy allowed
    MutexRaii(const MutexRaii&) = delete;
    void operator=(const MutexRaii&) = delete;
};

#define THREADS_NUM 1000
#define THREAD_COUNTER 20
int counter = 0;
Mutex g_mutex;

void* thread_func(void *args) {
    for(int i=0; i<THREAD_COUNTER; i++)
    {
        MutexRaii raii(&g_mutex);
        counter++;
    }
    return nullptr;
}

void raii_test() {
    pthread_t threads[THREADS_NUM];
    for(int i=0; i<THREADS_NUM; i++) {
        int ret = pthread_create(&threads[i], NULL, thread_func, NULL);
        if(ret) {
            std::cout << "pthread_create failed:" << ret << std::endl;
            return;
        }
    }

    for(int i=0; i<THREADS_NUM; i++) {
        pthread_join(threads[i], NULL);
    }

    std::cout << "after threads, counter:" << counter << std::endl;
}