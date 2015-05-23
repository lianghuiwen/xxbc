#include "thread.h"
#include <assert.h>

namespace xxbc {

Thread::Thread() : status_(kStopped), thread_() 
{
}

Thread::~Thread() 
{
    if (status_ == kRunning) {
        pthread_detach(thread_);
    }
}

void Thread::Start() 
{
    if (status_ == kStopped) {
        status_ = kRunning;
        int ret = pthread_create(&thread_, NULL, &Thread::ThreadFunc, this);
        assert(ret == 0);
    }
}

void Thread::Join() 
{
    if (status_ == kRunning) {
        status_ = kPending;
        pthread_join(thread_, NULL);
        status_ = kStopped;
    }
}

bool Thread::Alive() 
{
    return (status_ == kRunning);
}

void* Thread::ThreadFunc(void* param) 
{
    Thread* owner = static_cast<Thread*>(param);
    owner->Run();
    return NULL;
}

} // namespace xxbc
