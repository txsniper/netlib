#ifndef NETLIB_BASE_BLOCKINGQUEUE
#define NETLIB_BASE_BLOCKINGQUEUE

#include <deque>
#include <netlib/base/Mutex.h>
#include <netlib/base/Condition.h>
#include <netlib/base/noncopyable.h>

namespace netlib
{

namespace base
{

template <typename T>
class BlockingQueueT : netlib::base::noncopyable
{
    public:
        BlockingQueueT()
            : mutex_(), cond_(mutex_), queue_()
        {

        }

        void Push(const T& t)
        {
            MutexLockGuard guard(mutex_);
            queue_.push_back(t);
            cond_.notifyAll();
        }

        T pop()
        {
            MutexLockGuard guard(mutex_);
            while (queue_.empty()) {
                cond_wait();
            }
            T t = queue_.front();
            queue_.pop_front();
            return t;
        }

        size_t size()
        {
            MutexLockGuard guard(mutex_);
            return queue_.size();
        }

    private:
        Mutex mutex_;
        Condition cond_;
        std::deque<T> queue_;
};
}
}
#endif
