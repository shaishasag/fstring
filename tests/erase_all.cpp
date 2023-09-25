#include "gtest/gtest.h"
#include "fstring.h"

using namespace fixed;


TEST(EraseAll, erase_all_of)
{
    fstring31 f{"a0b1c2d3e4f5g6h7i8j9"};
    f.erase_all_of("abcdefghijklmnopqrstvwxyz");
    EXPECT_STREQ(f.c_str(), "0123456789");

    f.erase_all_of("abcdefghijklmnopqrstvwxyz");
    EXPECT_STREQ(f.c_str(), "0123456789");

    f.erase_all_of("0123456789");
    EXPECT_STREQ(f.c_str(), "");
}

TEST(EraseAll, erase_all_of_edge_cases)
{
    fstring31 f0{""};
    f0.erase_all_of("");
    EXPECT_STREQ(f0.c_str(), "");

    fstring31 f1{""};
    f1.erase_all_of("abcdefghijklmnopqrstvwxyz");
    EXPECT_STREQ(f1.c_str(), "");

    fstring31 f2{"a0b1c2d3e4f5g6h7i8j9"};
    f2.erase_all_of("");
    EXPECT_STREQ(f2.c_str(), "a0b1c2d3e4f5g6h7i8j9");
}

TEST(EraseAll, erase_all_not_of)
{
    fstring31 f{"a0b1c2d3e4f5g6h7i8j9"};
    f.erase_all_not_of("abcdefghijklmnopqrstvwxyz");
    EXPECT_STREQ(f.c_str(), "abcdefghij");

    f.erase_all_not_of("abcdefghijklmnopqrstvwxyz");
    EXPECT_STREQ(f.c_str(), "abcdefghij");

    f.erase_all_not_of("0123456789");
    EXPECT_STREQ(f.c_str(), "");
}

TEST(EraseAll, erase_all_not_of_edge_cases)
{
    fstring31 f0{""};
    f0.erase_all_not_of("");
    EXPECT_STREQ(f0.c_str(), "");

    fstring31 f1{""};
    f1.erase_all_not_of("abcdefghijklmnopqrstvwxyz");
    EXPECT_STREQ(f1.c_str(), "");

    fstring31 f2{"a0b1c2d3e4f5g6h7i8j9"};
    f2.erase_all_not_of("");
    EXPECT_STREQ(f2.c_str(), "");
}
