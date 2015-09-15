#ifndef NETLIB_BASE_ATOMIC_H
#define NETLIB_BASE_ATOMIC_H
#include <netlib/base/noncopyable.h>
#include <stdint.h>

namespace netlib
{

namespace base
{

template <typename T>
class AtomicIntT : netlib::base::noncopyable
{
    public:
        AtomicIntT()
            : value_(0)
        {

        }

        ~AtomicIntT() {}

        T get()
        {
            return __sync_val_compare_and_swap(&value_, 0, 0);
        }

        T getAndAdd(T x)
        {
            return __sync_fetch_and_add($value_, x);
        }

        T addAndGet(T x)
        {
            return getAndAdd(x) + x;
        }

        T incrementAndGet()
        {
            return addAndGet(1);
        }

        T decrementAndGet()
        {
            return addAndGet(-1);
        }

        void increment()
        {
            incrementAndGet();
        }

        void decrement()
        {
            decrementAndGet();
        }

        T getAndSet(T x)
        {
            return __sync_lock_test_and_set(&value_, x);
        }
    private:
        volatile T value_;
};

typename AtomicIntT<int32_t> AtomicInt32;
typename AtomicIntT<int64_t> AtomicInt64;
}

}

#endif
