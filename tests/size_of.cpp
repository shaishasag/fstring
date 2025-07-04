#include "gtest/gtest.h"
#include "fstring.h"

/// Verify expected object size
TEST(SizeOf, SizeOf)
{
    EXPECT_EQ(sizeof(fstr::fstring_base<0, char>), 24);
    EXPECT_EQ(sizeof(fstr::fstr15), 32);
    EXPECT_EQ(sizeof(fstr::fstr31), 48);
    EXPECT_EQ(sizeof(fstr::fstr63), 80);
    EXPECT_EQ(sizeof(fstr::fstr_ref), 8);
}
