#ifndef NETLIB_BASE_MUTEX_H
#define NETLIB_BASE_MUTEX_H

#include <netlib/base/noncopyable.h>
#include <pthread.h>

namespace netlib
{

namespace base
{
    class Mutex : netlib::base::noncopyable
    {
        public:
            Mutex()
            {
                pthread_mutex_init(&mutex_, NULL);
            }
            ~Mutex()
            {
                pthread_mutex_destroy(&mutex_);
            }

            void lock()
            {
                pthread_mutex_lock(&mutex_);
            }

            void unlock()
            {
                pthread_mutex_unlock(&mutex_);
            }

            pthread_mutex_t* getRawMutex()
            {
                return &mutex_;
            }

        private:
            pthread_mutex_t mutex_;
    };

    class MutexLockGuard
    {
        public:
            MutexLockGuard(Mutex& mutex_)
                : mutexlock_(mutex_)
            {
                mutexlock_.lock();
            }
            ~MutexLockGuard()
            {
                mutexlock_.unlock();
            }
        private:
            Mutex& mutexlock_;
    };
}

}
#endif
