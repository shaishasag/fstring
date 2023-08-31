#include "gtest/gtest.h"
#include "fstring.h"

TEST(SizeOf, SizeOf)
{
    EXPECT_EQ(sizeof(fixed::fstring_base<0, char>), 24);
    EXPECT_EQ(sizeof(fixed::fstring15), 32);
    EXPECT_EQ(sizeof(fixed::fstring31), 48);
    EXPECT_EQ(sizeof(fixed::fstring63), 80);
    EXPECT_EQ(sizeof(fixed::fstring_ref), 8);
}
