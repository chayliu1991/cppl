#include "../BlockingQueue.h"
#include "../CountDownLatch.h"
#include "../Thread.h"
#include "../Timestamp.h"

#include <map>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

class Bench
{
public:
    Bench(int numThreads) : latch_(numThreads)
    {
        threads_.reserve(numThreads);
        for (int i = 0; i < numThreads; ++i)
        {
            char name[32];
            snprintf(name, sizeof name, "work thread %d", i);
            threads_.emplace_back(new cppl::Thread(
                std::bind(&Bench::threadFunc, this), cppl::string(name)));
        }
        for (auto &thr : threads_)
        {
            thr->start();
        }
    }

    void run(int times)
    {
        printf("waiting for count down latch\n");
        latch_.wait();
        printf("all threads started\n");
        for (int i = 0; i < times; ++i)
        {
            cppl::Timestamp now(cppl::Timestamp::now());
            queue_.put(now);
            usleep(1000);
        }
    }

    void joinAll()
    {
        for (size_t i = 0; i < threads_.size(); ++i)
        {
            queue_.put(cppl::Timestamp::invalid());
        }

        for (auto &thr : threads_)
        {
            thr->join();
        }
    }

private:
    void threadFunc()
    {
        printf("tid=%d, %s started\n",
               cppl::CurrentThread::tid(),
               cppl::CurrentThread::name());

        std::map<int, int> delays;
        latch_.countDown();
        bool running = true;
        while (running)
        {
            cppl::Timestamp t(queue_.take());
            cppl::Timestamp now(cppl::Timestamp::now());
            if (t.valid())
            {
                int delay = static_cast<int>(timeDifference(now, t) * 1000000);
                // printf("tid=%d, latency = %d us\n",
                //        cppl::CurrentThread::tid(), delay);
                ++delays[delay];
            }
            running = t.valid();
        }

        printf("tid=%d, %s stopped\n",
               cppl::CurrentThread::tid(),
               cppl::CurrentThread::name());
        for (const auto &delay : delays)
        {
            printf("tid = %d, delay = %d, count = %d\n",
                   cppl::CurrentThread::tid(),
                   delay.first, delay.second);
        }
    }

    cppl::BlockingQueue<cppl::Timestamp> queue_;
    cppl::CountDownLatch latch_;
    std::vector<std::unique_ptr<cppl::Thread>> threads_;
};

int main(int argc, char *argv[])
{
    int threads = argc > 1 ? atoi(argv[1]) : 1;

    Bench t(threads);
    t.run(10000);
    t.joinAll();
}
