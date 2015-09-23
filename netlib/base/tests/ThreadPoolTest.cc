#include <netlib/base/ThreadPool.h>
#include <netlib/base/ThreadInfo.h>
#include <functional>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace netlib::base;

class Task
{
    public:
        void run()
        {
            int currTid = ThreadInfo::tid();
            fprintf(stdout,"CurrThread : %d run task\n", currTid);
            sleep(1);
        }
        ~Task()
        {

        }
};

int main()
{
    //Task taskVec[5];
    Task* taskVec[20];
    for(int i = 0; i < 20; i++)
    {
        taskVec[i] = new Task();
    }
    ThreadPool tp("threadpool", 3);
    tp.start();
    for(Task *a : taskVec)
    {
        tp.runTask(std::bind(&Task::run, a));
    }
    // 延迟10秒，否则任务还没来得及被线程池执行，线程池就马上退出了
    sleep(10);
    tp.stop();
    for(Task* a : taskVec)
    {
        delete a;
    }
}
