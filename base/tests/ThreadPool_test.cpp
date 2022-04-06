#include "../CountDownLatch.h"
#include "../CurrentThread.h"
#include "../Logging.h"
#include "../ThreadPool.h"

#include <stdio.h>
#include <unistd.h> // usleep

void print()
{
    printf("tid=%d\n", cppl::CurrentThread::tid());
}

void printString(const std::string &str)
{
    LOG_INFO << str;
    usleep(100 * 1000);
}

void test(int maxSize)
{
    LOG_WARN << "Test ThreadPool with max queue size = " << maxSize;
    cppl::ThreadPool pool("MainThreadPool");
    pool.setMaxQueueSize(maxSize);
    pool.start(5);

    LOG_WARN << "Adding";
    pool.run(print);
    pool.run(print);
    for (int i = 0; i < 100; ++i)
    {
        char buf[32];
        snprintf(buf, sizeof buf, "task %d", i);
        pool.run(std::bind(printString, std::string(buf)));
    }
    LOG_WARN << "Done";

    cppl::CountDownLatch latch(1);
    pool.run(std::bind(&cppl::CountDownLatch::countDown, &latch));
    latch.wait();
    pool.stop();
}

void longTask(int num)
{
    LOG_INFO << "longTask " << num;
    cppl::CurrentThread::sleepUsec(3000000);
}

void test2()
{
    LOG_WARN << "Test ThreadPool by stoping early.";
    cppl::ThreadPool pool("ThreadPool");
    pool.setMaxQueueSize(5);
    pool.start(3);

    cppl::Thread thread1([&pool]()
                         {
    for (int i = 0; i < 20; ++i)
    {
      pool.run(std::bind(longTask, i));
    } },
                         "thread1");
    thread1.start();

    cppl::CurrentThread::sleepUsec(5000000);
    LOG_WARN << "stop pool";
    pool.stop(); // early stop

    thread1.join();
    // run() after stop()
    pool.run(print);
    LOG_WARN << "test2 Done";
}

int main()
{
    test(0);
    test(1);
    test(5);
    test(10);
    test(50);
    test2();
}
