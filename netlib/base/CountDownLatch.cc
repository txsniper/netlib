#include <netlib/base/CountDownLatch.h>

namespace netlib
{
namespace base
{
    void CountDownLatch::wait()
    {
        MutexLockGuard guard(mutex_);
        while (count_!= 0)
        {
            cond_.wait();
        }
    }

    void CountDownLatch::countDown()
    {
        MutexLockGuard guard(mutex_);
        if (--count_ == 0)
        {
            cond_.notifyAll();
        }
    }

    int CountDownLatch::getCount()
    {
        MutexLockGuard guard(mutex_);
        return count_;
    }
}
}
