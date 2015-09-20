#ifndef NETLIB_BASE_THREAD
#define NETLIB_BASE_THREAD
#include <netlib/base/noncopyable.h>

#include <functional>
#include <string>
namespace netlib
{
namespace base
{

    class Thread : netlib::base::noncopyable
    {
        public:
            typedef std::function<void ()> ThreadFunc;
            Thread(std::string name, ThreadFunc func);

            void setFuncRunBegin(ThreadFunc func)
            {
                runBefore_ = func;
            }

            void setFuncRunAfter(ThreadFunc func)
            {
                runAfter_ = func;
            }

            bool start();
            bool started() const
            {
                return started_;
            }

            void join();

            bool joined() const
            {
                return joined_;
            }

        private:
            static void* beginThread(void *data);
            void runInThread();

        private:
            ThreadFunc threadFunc_;
            ThreadFunc runBefore_;
            ThreadFunc runAfter_;
            std::string threadName_;
            bool started_;
            bool joined_;
            int tId_;
            pthread_t pthreadId_;
    };
}
}
#endif
