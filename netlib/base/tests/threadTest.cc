#include <netlib/base/Thread.h>
#include <stdio.h>
class Test1
{
    public:
        Test1(int value)
            : b_(value)
        {

        }
        void func(int a)
        {
            int sum = a + b_;
            printf("the sum is %d\n", sum);
        }
    private:
        int b_;
};

int main(int argc, char** argv)
{
    Test1 test1(20);
    netlib::base::Thread t1("Test1",std::bind(&Test1::func, &test1, 15));
    t1.start();
    bool started = t1.started();
    printf("%d\n", started);
    if (started) {
        printf("thread started, lets join\n");
        t1.join();
    }
    return 0;
}
