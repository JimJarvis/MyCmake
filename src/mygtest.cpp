#include "myutils.h"
#include "mythreads.h"
#include <gtest/gtest.h>
#include <future>
using namespace std;

int sq(int i) { return i * i; }

TEST(MyTestSuite, Dudulu)
{
    EXPECT_EQ(1+2, 3) << "shitty";
    EXPECT_EQ(1+2, 4) << "shitty";
}

TEST(MyTestSuite, Async)
{
    future<int> res = async(sq, 13);
    EXPECT_EQ(res.get(), 169) << "async test fail";
}
