#ifndef NETLIB_BASE_COUNTDOWNLATCH
#define NETLIB_BASE_COUNTDOWNLATCH

#include <netlib/base/noncopyable.h>
#include <netlib/base/Mutex.h>
#include <netlib/base/Condition.h>

namespace netlib
{
namespace base
{

    class CountDownLatch : netlib::base::noncopyable
    {
        public:
            CountDownLatch(int count)
                : count_(count), mutex_(), cond_(mutex_)
            {

            }

            void wait();
            void countDown();
            int getCount();

        private:
            int count_;
            Mutex mutex_;
            Condition cond_;
    };
}
}
#endif
