#ifndef XXBC_MUTEXLOCK_H_
#define XXBC_MUTEXLOCK_H_

#include <pthread.h>

namespace xxbc {

class Mutex 
{
public:
    Mutex() {
        pthread_mutex_init(&mutex_, NULL);
    }

    ~Mutex() {
        pthread_mutex_destroy(&mutex_);
    }

    void Lock() {
        pthread_mutex_lock(&mutex_);
    }

    void Unlock() {
        pthread_mutex_unlock(&mutex_);
    }

    bool Trylock() {
        int ret = pthread_mutex_trylock(&mutex_);
        return ret == 0 ? true : false;
    }

private:
    // No copying allowed
    Mutex(const Mutex&);
    void operator=(const Mutex&);

private:
    friend class Condition;
    pthread_mutex_t mutex_;
};


class Condition 
{
public:
    Condition() {
        pthread_cond_init(&condition_, NULL);
    }

    ~Condition() {
        pthread_cond_destroy(&condition_);
    }

    void Wait(Mutex& mutex) {
        pthread_cond_wait(&condition_, &mutex.mutex_);
    }

    void Signal() {
        pthread_cond_signal(&condition_);
    }

private:
    // No copying allowed
    Condition(const Condition&);
    void operator=(const Condition&);

private:
    pthread_cond_t condition_;
};


class MutexLockGuard 
{
public:
    explicit MutexLockGuard(Mutex& mutex) : mutex_(mutex) {
        mutex_.Lock();
    }

    ~MutexLockGuard() {
        mutex_.Unlock();
    }

private:
    // No copying allowed
    MutexLockGuard(const MutexLockGuard&);
    void operator=(const MutexLockGuard&);

private:
    Mutex& mutex_;
};

} // namespace xxbc

#endif
