#include <netlib/base/ThreadPool.h>
#include <netlib/base/ThreadInfo.h>
#include <stdio.h>
namespace netlib
{
namespace base
{
    ThreadPool::ThreadPool(const std::string& name, int threadNum)
        : name_(name), threadNum_(threadNum), running_(false)
    {

    }

    ThreadPool::~ThreadPool()
    {
        if (running_)
        {
            stop();
        }
        for(int i=0; i< threadNum_; i++)
        {
            Thread* t = threadVec_[i];
            delete t;
        }
    }

    bool ThreadPool::start()
    {
        running_ = true;
        for(int i = 0; i < threadNum_; i++)
        {
            char workerName[20] = {0};
            snprintf(workerName, 20, "worker%d", i);
            std::string threadName = name_ + workerName;
            Thread* t = new Thread(threadName, std::bind(&ThreadPool::run, this));
            t->start();
            threadVec_.push_back(t);
        }
        return true;
    }

    void ThreadPool::defaultExitFunc()
    {
       // int currTid = ThreadInfo::tid();
       // printf("Thread %d exit\n", currTid);
    }

    bool ThreadPool::stop()
    {
        {
            MutexLockGuard guard(runningMutex_);
            running_ = false;
        }
        for(Thread* t : threadVec_)
        {
            (void)t;
            taskQueue_.push(std::bind(&ThreadPool::defaultExitFunc, this));
        }
        for(Thread* t : threadVec_)
        {
            t->join();
        }
        return true;
    }

    void ThreadPool::run()
    {
        while(true)
        {
            bool running = true;
            {
                // 检测执行标志
                MutexLockGuard guard(runningMutex_);
                running = running_;
            }
            // 可能任务线程池中还有任务未执行完成，也会退出
            if (!running)
            {
                break;
            }
            Task task = taskQueue_.pop();
            if (task)
            {
                task();
            }
        }
    }

    void ThreadPool::runTask(const Task& task)
    {
        taskQueue_.push(task);
    }

}
}
