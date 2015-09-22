#include <netlib/base/ThreadPool.h>
#include <netlib/base/ThreadInfo.h>
#include <functional>
#include <iostream>
#include <stdio.h>
using namespace netlib::base;

class Task
{
    public:
        void run()
        {
            int currTid = ThreadInfo::tid();
            for(int i=0; i<10; i++)
            {
                printf("CurrThread : %d run %d\n", currTid, i);
            }
        }
};
int main()
{
    Task taskVec[5];
    ThreadPool tp("threadpool", 3);
    for(Task a : taskVec)
    {
        tp.runTask(std::bind(&Task::run, &a));
    }
    tp.start();

}
