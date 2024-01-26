#include "gtest/gtest.h"
#include "fstring.h"

// Verify fixed::fstring::starts_with, fixed::fstring::ends_with, , fixed::fstring::contains
TEST(CompareTests, starts_ends_contains)
{
    {
        fixed::fstring31 original("The Psychedelic Furs");
        fixed::fstring31 reference(original);
        EXPECT_TRUE(original == reference);
        EXPECT_TRUE(original.starts_with('T'));
        EXPECT_TRUE(original.starts_with("The"));
        EXPECT_TRUE(original.ends_with("Furs"));
        EXPECT_TRUE(original.ends_with('s'));
        EXPECT_FALSE(original.starts_with("the"));
        EXPECT_FALSE(original.ends_with("furs"));
        EXPECT_TRUE(original.contains(""));
        EXPECT_TRUE(original.contains('d'));
        EXPECT_FALSE(original.contains('Z'));
        EXPECT_TRUE(original.contains("delic"));
        EXPECT_FALSE(original.contains("dElic"));
        EXPECT_TRUE(original.contains("The Psychedelic Furs"));
        
        EXPECT_TRUE(reference.starts_with('T'));
        EXPECT_TRUE(reference.starts_with("The"));
        EXPECT_TRUE(reference.ends_with("Furs"));
        EXPECT_TRUE(reference.ends_with('s'));
        EXPECT_FALSE(reference.starts_with("the"));
        EXPECT_FALSE(reference.ends_with("furs"));
        EXPECT_TRUE(reference.contains(""));
        EXPECT_TRUE(reference.contains('d'));
        EXPECT_FALSE(reference.contains('Z'));
        EXPECT_TRUE(reference.contains("delic"));
        EXPECT_FALSE(reference.contains("dElic"));
        EXPECT_TRUE(reference.contains("The Psychedelic Furs"));
    }
}

/// Verify fixed::fstring::operator==, fixed::fstring::compare
/// when used with const char*, std::string, std::string_view, ixed::fstring_ref
TEST(CompareTests, full_compare)
{
    const char* the_band = "K.C. and the sunshine band";
    {
        fixed::fstring31 kc(the_band);
        EXPECT_EQ(kc.compare(the_band), 0);
        EXPECT_TRUE(kc == the_band);
        EXPECT_TRUE(kc == std::string(the_band));
        EXPECT_TRUE(kc == std::string_view(the_band));

        fixed::fstring31 kc2(the_band);
        EXPECT_EQ(kc.compare(kc2), 0);
        EXPECT_EQ(kc.compare(fixed::fstring_ref(kc2)), 0);
    }
}

/// Verify fixed::fstring::compare, comparing partial strings
/// when used with const char*, std::string, std::string_view, fixed::fstring_ref
TEST(CompareTests, partial_compare)
{
    const char* the_band = "K.C. and the sunshine band";
    const char* the_sunshine = "sunshine";
    {
        fixed::fstring31 kc(the_band);
        EXPECT_EQ(kc.sv().compare(13, 8, the_sunshine), 0);
        EXPECT_EQ(kc.sv().compare(13, 8, the_band, 13, 8), 0);

        fixed::fstring31 ss2(the_sunshine);
        EXPECT_EQ(kc.sv().compare(13, 8, ss2), 0);
        EXPECT_EQ(kc.sv().compare(13, 8, fixed::fstring_ref(ss2)), 0);

        std::string_view ss_view(the_sunshine);
        EXPECT_EQ(kc.sv().compare(13, 8, ss_view), 0);

        std::string ss_str(the_sunshine);
        EXPECT_EQ(kc.sv().compare(13, 8, ss_str), 0);
    }
}

/// Verify fixed::fstring::icompare
TEST(CompareTests, case_insensitive)
{
    const char* the_band = "K.C. and the sunshine band";
    const char* the_sunshine = "k.c. and the sunshine BAND";
    {
        fixed::fstring31 kc(the_band);
        fixed::fstring31 ss(the_sunshine);
        
        EXPECT_EQ(kc.icompare(ss), 0);
        EXPECT_EQ(ss.icompare(kc), 0);

        kc += "A"; // now kc is longer and thus considered "bigger"
        EXPECT_GT(kc.icompare(ss), 0);
        EXPECT_LT(ss.icompare(kc), 0);

        ss += "a"; // now they are equal again
        EXPECT_EQ(kc.icompare(ss), 0);
        EXPECT_EQ(ss.icompare(kc), 0);

        ss += "b"; // now ss is "bigger"
        EXPECT_LT(kc.icompare(ss), 0);
        EXPECT_GT(ss.icompare(kc), 0);
    }
}
