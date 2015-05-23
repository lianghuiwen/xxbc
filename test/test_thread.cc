#include <stdio.h>
#include <unistd.h>
#include "thread.h"
using namespace xxbc;

class MyThread : public Thread 
{
public:
    virtual void Run() {
        quit_ = false;
        for (int i=0; i<10 && !quit_; ++i) {
            printf("thread running: %d\n", i);
            sleep(1);
        }
    }
    void Stop() { quit_ = true; }
    bool quit_;
};

int main(int argc, char* argv[])
{
    MyThread t;
    t.Start();
    sleep(5);
    t.Stop();
    t.Join();
}

