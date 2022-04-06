#include "../CurrentThread.h"
#include "../Thread.h"
#include "../ThreadLocalSingleton.h"

#include <stdio.h>

class Test : cppl::NonCopyable
{
public:
    Test()
    {
        printf("tid=%d, constructing %p\n", cppl::CurrentThread::tid(), this);
    }

    ~Test()
    {
        printf("tid=%d, destructing %p %s\n", cppl::CurrentThread::tid(), this, name_.c_str());
    }

    const cppl::string &name() const { return name_; }
    void setName(const cppl::string &n) { name_ = n; }

private:
    cppl::string name_;
};

void threadFunc(const char *changeTo)
{
    printf("tid=%d, %p name=%s\n",
           cppl::CurrentThread::tid(),
           &cppl::ThreadLocalSingleton<Test>::instance(),
           cppl::ThreadLocalSingleton<Test>::instance().name().c_str());
    cppl::ThreadLocalSingleton<Test>::instance().setName(changeTo);
    printf("tid=%d, %p name=%s\n",
           cppl::CurrentThread::tid(),
           &cppl::ThreadLocalSingleton<Test>::instance(),
           cppl::ThreadLocalSingleton<Test>::instance().name().c_str());

    // no need to manually delete it
    // cppl::ThreadLocalSingleton<Test>::destroy();
}

int main()
{
    cppl::ThreadLocalSingleton<Test>::instance().setName("main one");
    cppl::Thread t1(std::bind(threadFunc, "thread1"));
    cppl::Thread t2(std::bind(threadFunc, "thread2"));
    t1.start();
    t2.start();
    t1.join();
    printf("tid=%d, %p name=%s\n",
           cppl::CurrentThread::tid(),
           &cppl::ThreadLocalSingleton<Test>::instance(),
           cppl::ThreadLocalSingleton<Test>::instance().name().c_str());
    t2.join();

    pthread_exit(0);
}
