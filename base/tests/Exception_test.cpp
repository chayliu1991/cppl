#include "../CurrentThread.h"
#include "../Exception.h"
#include <functional>
#include <stdio.h>
#include <vector>

class Bar
{
public:
    void test()
    {
        printf("Stack:\n%s\n", cppl::CurrentThread::stackTrace(true).c_str());
        []
        {
            printf("Stack inside lambda:\n%s\n", cppl::CurrentThread::stackTrace(true).c_str());
        }();
        std::function<void()> func([]
                                   { printf("Stack inside std::function:\n%s\n", cppl::CurrentThread::stackTrace(true).c_str()); });
        func();

        func = std::bind(&Bar::callback, this);
        func();

        throw cppl::Exception("oops");
    }

private:
    void callback()
    {
        printf("Stack inside std::bind:\n%s\n", cppl::CurrentThread::stackTrace(true).c_str());
    }
};

void foo()
{
    Bar b;
    b.test();
}

int main()
{
    try
    {
        foo();
    }
    catch (const cppl::Exception &ex)
    {
        printf("reason: %s\n", ex.what());
        printf("stack trace:\n%s\n", ex.stackTrace());
    }
}
