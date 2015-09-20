#ifndef NETLIB_BASE_CONDITION
#define NETLIB_BASE_CONDITION

#include <pthread.h>
#include <netlib/base/noncopyable.h>
#include <netlib/base/Mutex.h>

namespace netlib
{
namespace base
{

    class Condition : netlib::base::noncopyable
    {
        public:
            Condition(Mutex& mutex)
                : mutex_(mutex)
            {
                pthread_cond_init(&cond_, NULL);
            }

            ~Condition()
            {
                pthread_cond_destroy(&cond_);
            }

            void wait()
            {
                pthread_cond_wait(&cond_, mutex_.getRawMutex());
            }

            void notify()
            {
                pthread_cond_signal(&cond_);
            }

            void notifyAll()
            {
                pthread_cond_broadcast(&cond_);
            }

            bool waitForSecs(unsigned int nSecs);
        private:
            Mutex& mutex_;
            pthread_cond_t cond_;
    };
}
}
#endif
