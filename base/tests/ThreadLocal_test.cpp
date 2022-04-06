#include "../CurrentThread.h"
#include "../Thread.h"
#include "../ThreadLocal.h"

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

cppl::ThreadLocal<Test> testObj1;
cppl::ThreadLocal<Test> testObj2;

void print()
{
    printf("tid=%d, obj1 %p name=%s\n",
           cppl::CurrentThread::tid(),
           &testObj1.value(),
           testObj1.value().name().c_str());
    printf("tid=%d, obj2 %p name=%s\n",
           cppl::CurrentThread::tid(),
           &testObj2.value(),
           testObj2.value().name().c_str());
}

void threadFunc()
{
    print();
    testObj1.value().setName("changed 1");
    testObj2.value().setName("changed 42");
    print();
}

int main()
{
    testObj1.value().setName("main one");
    print();
    cppl::Thread t1(threadFunc);
    t1.start();
    t1.join();
    testObj2.value().setName("main two");
    print();

    pthread_exit(0);
}
