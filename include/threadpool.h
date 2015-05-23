#ifndef XXBC_THREADPOOL_H_
#define XXBC_THREADPOOL_H_

#include <pthread.h>
#include <vector>
#include <queue>
#include "mutexlock.h"
using namespace std;

namespace xxbc {

class Task {
public:
    Task();
    virtual ~Task();
    virtual void DoWork() = 0;
};

class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();

    void Initialize(uint32_t count);
    void Destroy();
    void AssignTask(Task* task);
    Task* FetchTask();

private:
    static void* ThreadFunc(void* param);

    // No copying allowed
    ThreadPool(const ThreadPool&);
    void operator=(const ThreadPool&);

private:
    bool shutdown_;
    Mutex mutex_;
    Condition condition_;
    queue<Task*> tasks_;
    vector<pthread_t> threads_;
};

} // namespace xxbc

#endif
