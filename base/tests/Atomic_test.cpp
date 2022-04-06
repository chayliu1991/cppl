#include "../Atomic.h"
#include <assert.h>

#include "gtest/gtest.h"

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

int main()
{
    testing::InitGoogleTest();
    auto res = RUN_ALL_TESTS();
    (void)res;
    return 0;
    // {
    //     cppl::AtomicInt64 a0;
    //     assert(a0.get() == 0);
    //     assert(a0.getAndAdd(1) == 0);
    //     assert(a0.get() == 1);
    //     assert(a0.addAndGet(2) == 3);
    //     assert(a0.get() == 3);
    //     assert(a0.incrementAndGet() == 4);
    //     assert(a0.get() == 4);
    //     a0.increment();
    //     assert(a0.get() == 5);
    //     assert(a0.addAndGet(-3) == 2);
    //     assert(a0.getAndSet(100) == 2);
    //     assert(a0.get() == 100);
    // }

    // {
    //     cppl::AtomicInt32 a1;
    //     assert(a1.get() == 0);
    //     assert(a1.getAndAdd(1) == 0);
    //     assert(a1.get() == 1);
    //     assert(a1.addAndGet(2) == 3);
    //     assert(a1.get() == 3);
    //     assert(a1.incrementAndGet() == 4);
    //     assert(a1.get() == 4);
    //     a1.increment();
    //     assert(a1.get() == 5);
    //     assert(a1.addAndGet(-3) == 2);
    //     assert(a1.getAndSet(100) == 2);
    //     assert(a1.get() == 100);
    // }
}
