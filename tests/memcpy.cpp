#include "gtest/gtest.h"
#include "fstring.h"

//using namespace fstr;

struct SomeStrings
{
    fstr::fstr7  m1;
    fstr::fstr15 m3;
    fstr::fstr31 m5;
};

TEST(Memcopy, memcpy)
{
    {   // fstr::fstring_base should be memcpy-able
        SomeStrings someone{"a", "b", "c"};
        SomeStrings sometwo;

        memcpy(&sometwo, &someone, sizeof(SomeStrings));
        ASSERT_STREQ(someone.m1.c_str(), sometwo.m1.c_str());
        ASSERT_STREQ(someone.m3.c_str(), sometwo.m3.c_str());
        ASSERT_STREQ(someone.m5.c_str(), sometwo.m5.c_str());
    }
}
