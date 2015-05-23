#ifndef XXBC_THREAD_H_
#define XXBC_THREAD_H_

#include <pthread.h>

namespace xxbc {

class Thread 
{
public:
    enum Status {
        kStopped,
        kPending,
        kRunning
    };

    Thread();
    virtual ~Thread();

    void Start();
    void Join();
    bool Alive();

protected:
    virtual void Run() = 0;

private:
    static void* ThreadFunc(void* param);

    // No copying allowed
    Thread(const Thread&);
    void operator=(const Thread&);

private:
    Status status_;
    pthread_t thread_;
};

} // namespace xxbc

#endif
