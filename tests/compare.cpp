#include "gtest/gtest.h"
#include "fstring.h"

TEST(CompareTests, starts_ends_contains)
{
    {
        fixed::fstring31 l("The Psychedelic Furs");
        fixed::fstring31 r("The Psychedelic Furs");
        EXPECT_TRUE(l == r);
        EXPECT_TRUE(l.starts_with('T'));
        EXPECT_TRUE(l.starts_with("The"));
        EXPECT_TRUE(l.ends_with("Furs"));
        EXPECT_TRUE(l.ends_with('s'));
        EXPECT_FALSE(l.starts_with("the"));
        EXPECT_FALSE(l.ends_with("furs"));
        EXPECT_TRUE(l.contains(""));
        EXPECT_TRUE(l.contains('d'));
        EXPECT_FALSE(l.contains('Z'));
        EXPECT_TRUE(l.contains("delic"));
        EXPECT_FALSE(l.contains("dElic"));
        EXPECT_TRUE(l.contains("The Psychedelic Furs"));
        EXPECT_FALSE(l.contains("The Psychedelic Furs+The Sisters of Mercy"));

        r = "The Sisters of Mercy";
        EXPECT_FALSE(l == r);
        EXPECT_TRUE(r.starts_with("The"));
        EXPECT_TRUE(r.ends_with("Mercy"));
        EXPECT_FALSE(l.starts_with("the"));
        EXPECT_FALSE(l.ends_with("mercy"));
    }
}

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

        std::string_view kc_view(the_band);
        EXPECT_EQ(kc.compare(kc_view), 0);

        std::string kc_str(the_band);
        EXPECT_EQ(kc.compare(kc_str), 0);
    }
}

TEST(CompareTests, partial_compare)
{
    const char* the_band = "K.C. and the sunshine band";
    const char* the_sunshine = "sunshine";
    {
        fixed::fstring31 kc(the_band);
        EXPECT_EQ(kc.compare(13, 8, the_sunshine), 0);
        EXPECT_EQ(kc.compare(13, 8, the_band, 13, 8), 0);

        fixed::fstring31 ss2(the_sunshine);
        EXPECT_EQ(kc.compare(13, 8, ss2), 0);
        EXPECT_EQ(kc.compare(13, 8, fixed::fstring_ref(ss2)), 0);

        std::string_view ss_view(the_sunshine);
        EXPECT_EQ(kc.compare(13, 8, ss_view), 0);

        std::string ss_str(the_sunshine);
        EXPECT_EQ(kc.compare(13, 8, ss_str), 0);
    }
}

TEST(CompareTests, case_insensitive)
{
    const char* the_band = "K.C. and the sunshine band";
    const char* the_sunshine = "k.c. and the sunshine BAND";
    {
        fixed::fstring31 kc(the_band);
        fixed::fstring31 ss(the_sunshine);
        EXPECT_EQ(kc.icompare(ss), 0);
        EXPECT_EQ(ss.icompare(kc), 0);

        kc += "A"; // now kc is "bigger"
        EXPECT_GT(kc.icompare(ss), 0);
        EXPECT_LT(ss.icompare(kc), 0);

        ss += "a"; // no they are equal again
        EXPECT_EQ(kc.icompare(ss), 0);
        EXPECT_EQ(ss.icompare(kc), 0);

        ss += "b"; // now ss is "bigger"
        EXPECT_LT(kc.icompare(ss), 0);
        EXPECT_GT(ss.icompare(kc), 0);
    }
}
