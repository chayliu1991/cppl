#include "../Atomic.h"
#include <assert.h>

#include "gtest/gtest.h"

using ::testing::InitGoogleTest;

TEST(AtomicTest, AtomicInt64)
{
    cppl::AtomicInt64 a0;
    EXPECT_EQ(0, a0.get());
    EXPECT_EQ(0, a0.getAndAdd(1));
    EXPECT_EQ(1, a0.get());
    EXPECT_EQ(3, a0.addAndGet(2));
    EXPECT_EQ(3, a0.get());
    EXPECT_EQ(4, a0.incrementAndGet());
    EXPECT_EQ(4, a0.get());
    a0.increment();
    EXPECT_EQ(5, a0.get());
    EXPECT_EQ(2, a0.addAndGet(-3));
    EXPECT_EQ(2, a0.getAndSet(100));
    std::cout << a0.get() << std::endl;
    EXPECT_EQ(100, a0.get());
}

TEST(AtomicTest, AtomicInt32)
{
    cppl::AtomicInt32 a0;
    EXPECT_EQ(0, a0.get());
    EXPECT_EQ(0, a0.getAndAdd(1));
    EXPECT_EQ(1, a0.get());
    EXPECT_EQ(3, a0.addAndGet(2));
    EXPECT_EQ(3, a0.get());
    EXPECT_EQ(4, a0.incrementAndGet());
    EXPECT_EQ(4, a0.get());
    a0.increment();
    EXPECT_EQ(5, a0.get());
    EXPECT_EQ(2, a0.addAndGet(-3));
    EXPECT_EQ(2, a0.getAndSet(100));
    std::cout << a0.get() << std::endl;
    EXPECT_EQ(100, a0.get());
}

int main()
{
    InitGoogleTest();
    return RUN_ALL_TESTS();
}
