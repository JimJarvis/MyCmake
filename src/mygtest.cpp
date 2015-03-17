#include "myutils.h"
#include <gtest/gtest.h>
using namespace std;

TEST(MyTestSuite, Dudulu)
{
    EXPECT_EQ(1+2, 3) << "shitty";
    EXPECT_EQ(1+2, 4) << "shitty";
}
