#include "gtest/gtest.h"
#include "fstring.h"


static void CompareRefToCharPtr(fstr::fstr_ref in_ref, const char* in_str)
{
    EXPECT_STREQ(in_ref.c_str(), in_str);
}

template<class TOriginal>
static void IsRefAndOriginalTheSame(fstr::fstr_ref in_ref, TOriginal& in_origi)
{
    EXPECT_EQ(in_origi.capacity(), in_ref.capacity());
    EXPECT_EQ(in_origi.c_str(), in_ref.c_str());
    EXPECT_STREQ(in_origi.c_str(), in_ref.c_str());
    EXPECT_EQ(in_origi.empty(), in_ref.empty());
    EXPECT_EQ(in_origi.full(), in_ref.full());
    EXPECT_EQ(in_origi.size(), in_ref.size());
}


TEST(RefTests, RefIsCorrect)
{
    {
        fstr::fstr15 ms1 = "umaguma";
        fstr::fstr_ref ref1(ms1);
        IsRefAndOriginalTheSame(ref1, ms1);

        ref1 += "Shin";
        IsRefAndOriginalTheSame(ref1, ms1);

        ms1 += " G";
        IsRefAndOriginalTheSame(ref1, ms1);
    }
    {
        fstr::fstr15 ms1 = "umaguma";
        fstr::fstr_ref ref1(ms1);
        IsRefAndOriginalTheSame(ref1, ms1);

        ref1.clear();
        IsRefAndOriginalTheSame(ref1, ms1);
    }
    {
        fstr::fstr15 ms1 = "umaguma";
        fstr::fstr_ref ref1(ms1);
        IsRefAndOriginalTheSame(ref1, ms1);

        ms1.clear();
        IsRefAndOriginalTheSame(ref1, ms1);
    }
}

static fstr::fstr_ref Passover(fstr::fstr_ref in_ref)
{
    return in_ref;
}


TEST(RefTests, PassToFunc)
{
    {
        // pass to func as ref explicit
        fstr::fstr15 ms1 = "umaguma";
        fstr::fstr_ref ref1 = Passover(fstr::fstr_ref(ms1));
        CompareRefToCharPtr(ref1, "umaguma");
        EXPECT_EQ(ref1.capacity(), 15);
        EXPECT_STREQ(ref1.c_str(), "umaguma");
        EXPECT_STRNE(ref1.c_str(), "umaguma?");
        EXPECT_FALSE(ref1.empty());
        EXPECT_FALSE(ref1.full());
        EXPECT_EQ(ref1.size(), 7);
    }
    {
        // pass to func as ref implicit
        fstr::fstr15 ms1 = "umaguma";
        fstr::fstr_ref ref1 = Passover(ms1);
        CompareRefToCharPtr(ref1, "umaguma");
        EXPECT_EQ(ref1.capacity(), 15);
        EXPECT_STREQ(ref1.c_str(), "umaguma");
        EXPECT_STRNE(ref1.c_str(), "umaguma?");
        EXPECT_FALSE(ref1.empty());
        EXPECT_FALSE(ref1.full());
        EXPECT_EQ(ref1.size(), 7);
    }
}
