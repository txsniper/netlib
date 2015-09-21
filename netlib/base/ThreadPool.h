#ifndef NETLIB_BASE_THREADPOOL
#define NETLIB_BASE_THREADPOOL

#include <netlib/base/noncopyable.h>
#include <netlib/base/Thread.h>
#include <netlib/base/Mutex.h>
#include <netlib/base/BlockingQueue.h>

#include <functional>
#include <string>
#include <vector>
namespace netlib
{

namespace base
{
    class ThreadPool : netlib::base::noncopyable
    {
        public:
            typedef std::function<void ()> Task;
            ThreadPool(const std::string& name, int threadNum);
            ~ThreadPool();
            bool start();
            bool stop();
            void runTask(const Task& task);
        private:
            void run();
            std::string name_;
            int threadNum_;
            bool running_;
            Mutex runningMutex_;
            std::vector<Thread*> threadVec_;
            BlockingQueueT<Task> taskQueue_;

    };
}
}
#endif
