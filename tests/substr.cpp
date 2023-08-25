#include "gtest/gtest.h"
#include "fstring.h"

TEST(Substr, by_possition_only)
{
    {
        const fixed::fstring31 full("Masayoshi Takanaka");
        EXPECT_TRUE(full.sv().substr(0) == "Masayoshi Takanaka");
        EXPECT_TRUE(full.sv().substr(10) == "Takanaka");
        EXPECT_TRUE(full.sv().substr(18).empty());
    }
}

TEST(Substr, by_possition_and_count)
{
    {
        const fixed::fstring31 full("Masayoshi Takanaka");
        EXPECT_TRUE(full.sv().substr(0, 18) == "Masayoshi Takanaka");
        EXPECT_TRUE(full.sv().substr(0, 17) == "Masayoshi Takanak");
        EXPECT_TRUE(full.sv().substr(1, 18) == "asayoshi Takanaka");
        EXPECT_TRUE(full.sv().substr(1, 17) == "asayoshi Takanaka");
        EXPECT_TRUE(full.sv().substr(10, 8) == "Takanaka");
        EXPECT_TRUE(full.sv().substr(10, 9) == "Takanaka");
        EXPECT_TRUE(full.sv().substr(10, 6) == "Takana");
    }
}
