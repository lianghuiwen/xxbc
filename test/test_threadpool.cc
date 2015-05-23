#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"
using namespace xxbc;

class MyTask : public Task 
{
public:
    virtual void DoWork() {
        for (int i=1; i<6; ++i) {
            printf("thread running: %d\n", i);
            sleep(1);
        }
    }
};

int main(int argc, char* argv[])
{
    ThreadPool pool;
    pool.Initialize(3);
    for (int i=0; i<10; ++i) {
        MyTask* task = new MyTask();
        pool.AssignTask(task);
    }
    sleep(8);
    pool.Destroy();
}

