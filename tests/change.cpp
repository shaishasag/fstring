#include "gtest/gtest.h"
#include "fstring.h"


/// A helper function to verify that a fstr::fstr_base and it's reference are the same
template<class TOriginal>
static void IsRefAndOriginalTheSame(fstr::fstr_ref in_ref, TOriginal& in_origi)
{
    EXPECT_EQ(in_origi.c_str(), in_ref.c_str());    // pointers should be the same
    EXPECT_STREQ(in_origi.c_str(), in_ref.c_str()); // contents should be the same
    EXPECT_EQ(in_origi.capacity(), in_ref.capacity());
    EXPECT_EQ(in_origi.empty(), in_ref.empty());
    EXPECT_EQ(in_origi.full(), in_ref.full());
    EXPECT_EQ(in_origi.size(), in_ref.size());
}

TEST(ChangesTests, OriginalVsReference)
{
    {
        fstr::fstr31 original = "umaguma";
        fstr::fstr_ref reference(original);
        IsRefAndOriginalTheSame(reference, original);

        // changing the ref, should also change the original
        reference[1] = 'M';
        EXPECT_STREQ(original.c_str(), "uMaguma");
        EXPECT_STRNE(original.c_str(), "umaguma");
        EXPECT_EQ(original.size(), 7);
        IsRefAndOriginalTheSame(reference, original);

        // change the original, should also change the ref
        original[6] = 'A';
        EXPECT_STREQ(reference.c_str(), "uMagumA");
        EXPECT_STRNE(reference.c_str(), "uMaguma");
        EXPECT_EQ(reference.size(), 7);
        IsRefAndOriginalTheSame(reference, original);
    }
}

/// Verify fstr::fstr_base::remove_prefix, fstr::fstr_base::remove_suffix
TEST(ChangesTests, PresfixDuffix)
{
    {
        fstr::fstr31 l("The Psychedelic Furs");
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
