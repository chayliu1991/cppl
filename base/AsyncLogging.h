#pragma once

#include "BlockingQueue.h"
#include "BoundedBlockingQueue.h"
#include "CountDownLatch.h"
#include "LogStream.h"
#include "Mutex.h"
#include "Thread.h"

#include <atomic>
#include <vector>

namespace cppl
{
    class AsyncLogging : NonCopyable
    {
    public:
        AsyncLogging(const string &basename,
                     off_t rollSize,
                     int flushInterval = 3);

        ~AsyncLogging()
        {
            if (running_)
            {
                stop();
            }
        }

        void append(const char *logline, int len);

        void start()
        {
            running_ = true;
            thread_.start();
            latch_.wait();
        }

        void stop()
        {
            running_ = false;
            cond_.notify();
            thread_.join();
        }

    private:
        void threadFunc();

        typedef cppl::detail::FixedBuffer<cppl::detail::kLargeBuffer> Buffer;
        typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
        typedef BufferVector::value_type BufferPtr;

        const int flushInterval_;
        std::atomic<bool> running_;
        const string basename_;
        const off_t rollSize_;
        cppl::Thread thread_;
        cppl::CountDownLatch latch_;
        cppl::MutexLock mutex_;
        cppl::Condition cond_;
        BufferPtr currentBuffer_;
        BufferPtr nextBuffer_;
        BufferVector buffers_;
    };
}