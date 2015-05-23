#include "threadpool.h"
#include <assert.h>

namespace xxbc {

Task::Task() {}

Task::~Task() {}

ThreadPool::ThreadPool() : shutdown_(false), mutex_(), condition_(), tasks_(), threads_() 
{
}

ThreadPool::~ThreadPool() 
{
    if (!shutdown_) {
        Destroy();
    }   
}

void ThreadPool::Initialize(uint32_t count) 
{
    pthread_t threadid;
    threads_.reserve(count);
    for (uint32_t i = 0; i < count; ++i) {
        int ret = pthread_create(&threadid, NULL, &ThreadPool::ThreadFunc, this);
        assert(ret == 0);
        threads_.push_back(threadid);
    }
}

void ThreadPool::Destroy() 
{
    shutdown_ = true;
    condition_.Signal();
    for (uint32_t i = 0; i < threads_.size(); ++i) {
        pthread_join(threads_[i], NULL);
    }
}

void ThreadPool::AssignTask(Task* task) 
{
    MutexLockGuard lock(mutex_);
    tasks_.push(task);
    condition_.Signal();
}

Task* ThreadPool::FetchTask() 
{
    MutexLockGuard lock(mutex_);
    while (!shutdown_ && tasks_.empty()) {
        condition_.Wait(mutex_);
    }
    
    Task* task = NULL;
    if (!tasks_.empty()) {
        task = tasks_.front();
        tasks_.pop();
    }
    return task;
}

void* ThreadPool::ThreadFunc(void* param) 
{
    ThreadPool* owner = static_cast<ThreadPool*>(param);
    while (!owner->shutdown_) {
        Task* task = owner->FetchTask();
        if (task != NULL) {
            task->DoWork();
            delete task;
        }
    }
    return 0;
}

} // namespace xxbc
