#include "gtest/gtest.h"
#include "fstring.h"

TEST(variadic, variadic_basic_types)
{
    {   // variadic short
        constexpr fixed::fstring31 vari("a", "b", "c", "d");
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


TEST(variadic, variadic_more_types)
{
    {   // variadic short
        fixed::fstring31 vari(fixed::fstring7("a"), "b", fixed::fstring7("c"), "d");
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
        std::string_view a_sv("aa");
        std::string b_s("bb");
        fixed::fstring15 c_fs("cc");
        const char* d_chp{"dd"};

        fixed::fstring31 vari1(a_sv, b_s, c_fs, d_chp);
        EXPECT_STREQ(vari1.c_str(), "aabbccdd");
        EXPECT_EQ(vari1.size(), 8);

        // different order...
        fixed::fstring31 vari2(d_chp, a_sv, c_fs, b_s);
        EXPECT_STREQ(vari2.c_str(), "ddaaccbb");
        EXPECT_EQ(vari2.size(), 8);
    }

}

