#include "gtest/gtest.h"
#include "fstring.h"

TEST(Substr, by_possition_only)
{
    {
        const fixed::fstring31 full("Masayoshi Takanaka");
        EXPECT_STREQ(full.substr(0).c_str(), "Masayoshi Takanaka");
        EXPECT_STREQ(full.substr(10).c_str(), "Takanaka");
        EXPECT_TRUE(full.substr(18).empty());
        EXPECT_TRUE(full.substr(19).empty());
        EXPECT_TRUE(full.substr(19976554).empty());
    }
}

TEST(Substr, by_possition_and_count)
{
    {
        const fixed::fstring31 full("Masayoshi Takanaka");
        EXPECT_STREQ(full.substr(0, 18).c_str(), "Masayoshi Takanaka");
        EXPECT_STREQ(full.substr(0, 17).c_str(), "Masayoshi Takanak");
        EXPECT_STREQ(full.substr(1, 18).c_str(), "asayoshi Takanaka");
        EXPECT_STREQ(full.substr(1, 17).c_str(), "asayoshi Takanaka");
        EXPECT_STREQ(full.substr(10, 8).c_str(), "Takanaka");
        EXPECT_STREQ(full.substr(10, 9).c_str(), "Takanaka");
        EXPECT_STREQ(full.substr(10, 6).c_str(), "Takana");
        EXPECT_TRUE(full.substr(19976554, 293847).empty());
    }
}
