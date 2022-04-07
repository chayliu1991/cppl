#include "../Any.h"

#include <string>
#include <iostream>


#include "gtest/gtest.h"


using ::testing::InitGoogleTest;

using namespace cppl;

TEST(AnyTest,any)
{
    Any n;
    EXPECT_TRUE(n.is_null());
    std::string  s1 = "hello";
    n = s1;
    n = "world";
    // EXPECT_EQ("world",n.any_cast<std::string>());
    std::cout<<n.any_cast<std::string>()<<std::endl;

    // Any n1 = 1;
    // EXPECT_EQ(n.any_cast<int>(),1);
}

int main(int argc,char** argv)
{
    InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}