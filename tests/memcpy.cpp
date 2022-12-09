#include "gtest/gtest.h"
#include "fstring.h"

//using namespace fixed;

struct SomeStrings
{
    fixed::fstring7  m1;
    fixed::fstring15 m3;
    fixed::fstring31 m5;
};

TEST(Memcopy, memcpy)
{
    {   // fixed::fstring_base should be memcpy-able
        SomeStrings someone{"a", "b", "c"};
        SomeStrings sometwo;

        memcpy(&sometwo, &someone, sizeof(SomeStrings));
        ASSERT_STREQ(someone.m1.c_str(), sometwo.m1.c_str());
        ASSERT_STREQ(someone.m3.c_str(), sometwo.m3.c_str());
        ASSERT_STREQ(someone.m5.c_str(), sometwo.m5.c_str());
    }
}
