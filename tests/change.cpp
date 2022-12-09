#include "gtest/gtest.h"
#include "fstring.h"


template<class TOriginal>
static void IsRefAndOriginalTheSame(fixed::fstring_ref in_ref, TOriginal& in_origi)
{
    EXPECT_EQ(in_origi.capacity(), in_ref.capacity());
    EXPECT_EQ(in_origi.c_str(), in_ref.c_str());
    EXPECT_STREQ(in_origi.c_str(), in_ref.c_str());
    EXPECT_EQ(in_origi.empty(), in_ref.empty());
    EXPECT_EQ(in_origi.full(), in_ref.full());
    EXPECT_EQ(in_origi.size(), in_ref.size());
}

TEST(ChangesTests, AsArray)
{
    {
        fixed::fstring31 ms1 = "umaguma";
        fixed::fstring_ref ref1(ms1);
        IsRefAndOriginalTheSame(ref1, ms1);

        // change the ref, should also change the original
        ref1[1] = 'M';
        EXPECT_STREQ(ms1.c_str(), "uMaguma");
        EXPECT_STRNE(ms1.c_str(), "umaguma");
        EXPECT_EQ(ms1.size(), 7);
        IsRefAndOriginalTheSame(ref1, ms1);

        // change the original, does it change the ref?
        ms1[6] = 'A';
        EXPECT_STREQ(ref1.c_str(), "uMagumA");
        EXPECT_STRNE(ref1.c_str(), "uMaguma");
        EXPECT_EQ(ref1.size(), 7);
        IsRefAndOriginalTheSame(ref1, ms1);
    }
}

TEST(ChangesTests, PresfixDuffix)
{
    {
        fixed::fstring31 l("The Psychedelic Furs");
        l.remove_prefix(0);
        ASSERT_TRUE(l.compare("The Psychedelic Furs") == 0);
        l.remove_suffix(0);
        ASSERT_TRUE(l.compare("The Psychedelic Furs") == 0);

        l.remove_prefix(1);
        ASSERT_TRUE(l.compare("he Psychedelic Furs") == 0);
        l.remove_suffix(1);
        ASSERT_TRUE(l.compare("he Psychedelic Fur") == 0);

        l.remove_prefix(3);
        ASSERT_TRUE(l.compare("Psychedelic Fur") == 0);
        l.remove_suffix(4);
        ASSERT_TRUE(l.compare("Psychedelic") == 0);

        l.remove_prefix(l.size());
        ASSERT_TRUE(l.empty());

        l = "Oingo Boingo";
        l.remove_suffix(l.size());
        ASSERT_TRUE(l.empty());
    }
}
