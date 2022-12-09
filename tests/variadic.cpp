#include "gtest/gtest.h"
#include "fstring.h"

TEST(variadic, variadic_1)
{
    {   // variadic short
        fixed::fstring31 vari("a", "b", "c", "d");
        EXPECT_STREQ(vari.c_str(), "abcd");
        EXPECT_FALSE(vari.empty());
        EXPECT_FALSE(vari.full());
        EXPECT_EQ(vari.size(), 4);
    }
    {   // variadic too long
        fixed::fstring7 vari("aa1", "bb2", "cc3");
        EXPECT_STREQ(vari.c_str(), "aa1bb2c");
        EXPECT_FALSE(vari.empty());
        EXPECT_TRUE(vari.full());
        EXPECT_EQ(vari.size(), 7);
    }
    {   // variadic mixed basic types
        fixed::fstring31 vari("aa", '1', "bb", '2', "cc");
        EXPECT_STREQ(vari.c_str(), "aa1bb2cc");
        EXPECT_FALSE(vari.empty());
        EXPECT_FALSE(vari.full());
        EXPECT_EQ(vari.size(), 8);
    }

}
