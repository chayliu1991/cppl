#include "../CurrentThread.h"
#include "../Singleton.h"
#include "../Thread.h"

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

class TestNoDestroy : cppl::NonCopyable
{
public:
    // Tag member for Singleton<T>
    void no_destroy();

    TestNoDestroy()
    {
        printf("tid=%d, constructing TestNoDestroy %p\n", cppl::CurrentThread::tid(), this);
    }

    ~TestNoDestroy()
    {
        printf("tid=%d, destructing TestNoDestroy %p\n", cppl::CurrentThread::tid(), this);
    }
};

void threadFunc()
{
    printf("tid=%d, %p name=%s\n",
           cppl::CurrentThread::tid(),
           &cppl::Singleton<Test>::instance(),
           cppl::Singleton<Test>::instance().name().c_str());
    cppl::Singleton<Test>::instance().setName("only one, changed");
}

int main()
{
    cppl::Singleton<Test>::instance().setName("only one");
    cppl::Thread t1(threadFunc);
    t1.start();
    t1.join();
    printf("tid=%d, %p name=%s\n",
           cppl::CurrentThread::tid(),
           &cppl::Singleton<Test>::instance(),
           cppl::Singleton<Test>::instance().name().c_str());
    cppl::Singleton<TestNoDestroy>::instance();
    printf("with valgrind, you should see %zd-byte memory leak.\n", sizeof(TestNoDestroy));
}
