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
                pthread_mutex_init(&mutex_);
            }
            ~Mutex()
            {
                pthread_mutex_destroy(&mutex_);
            }

            void lock()
            {
                pthread_mutex_lock(&mutex_);
            }

            void unLock()
            {
                pthread_mutex_unlock(&mutex_);
            }

        private:
            pthread_mutext_t mutex_;
    };

    class MutexLockGuard
    {
        public:
            MutexLock(Mutex& mutex_)
                : mutexlock_(mutex_)
            {
                mutexlock_.lock();
            }
            ~MutexLock()
            {
                mutexlock_.unlock();
            }
        private:
            Mutex& mutexlock_;
    }
}

}
#endif
