#include <netlib/base/BlockingQueue.h>
#include <netlib/base/Thread.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
typedef netlib::base::BlockingQueueT<std::string> StringQueue;
StringQueue stringQueue;
class Consumer
{
    public:
        Consumer(const std::string& name, StringQueue* q)
            : name_(name), queue_(q)
        {

        }

        ~Consumer()
        {
            delete thread_;
        }

        void run()
        {
            while(true)
            {
                std::string str= queue_->pop();
                std::cout<<name_<<" print "<< str <<std::endl;
                if(str == "quit")
                {
                    break;
                }
            }
        }
        void start()
        {
            thread_ = new netlib::base::Thread(name_, std::bind(&Consumer::run, this));
            thread_->start();
        }
        void join()
        {
            thread_->join();
        }
    private:
        std::string name_;
        StringQueue* queue_;
        netlib::base::Thread *thread_;
};

class Provider
{
    public:
        Provider(const std::string& name, int num, StringQueue* q)
            : name_(name), num_(num), queue_(q)
        {

        }

        ~Provider()
        {
            delete thread_;
        }

        void run()
        {
            for(int i=0; i < num_; i++)
            {
                char buf[20] = {0};
                snprintf(buf, 20, "[%s str%d]", name_.c_str(), i);
                queue_->push(buf);
            }
            queue_->push("quit");
        }

        void start()
        {
            thread_ = new netlib::base::Thread(name_, std::bind(&Provider::run, this));
            thread_->start();
        }

        void join()
        {
            thread_->join();
        }
    private:
        std::string name_;
        int num_;
        StringQueue* queue_;
        netlib::base::Thread * thread_;

};

int main()
{
    std::vector<Consumer*> arrConsumer;
    std::vector<Provider*> arrProvider;
    for(int i=0; i < 4; i++)
    {
        char buf[20] = {0};
        snprintf(buf, 20, "Consumer%d", i);
        arrConsumer.push_back(new Consumer(buf, &stringQueue));
    }
    for(int i=0; i < 4; i++)
    {
        char buf[20] = {0};
        snprintf(buf, 20, "Provider%d", i);
        arrProvider.push_back(new Provider(buf, 4, &stringQueue));
    }
    for(Consumer* a: arrConsumer) {
        a->start();
    }
    for(Provider* a: arrProvider) {
        a->start();
    }
    for(Consumer* a: arrConsumer) {
        a->join();
    }
    for(Provider* a: arrProvider) {
        a->join();
    }
    return 0;
}
