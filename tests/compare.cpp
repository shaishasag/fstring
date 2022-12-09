#include "gtest/gtest.h"
#include "fstring.h"

TEST(CompareTests, operator_equal)
{
    {
        fixed::fstring31 l("The Psychedelic Furs");
        fixed::fstring31 r("The Psychedelic Furs");
        ASSERT_TRUE(l == r);
        ASSERT_TRUE(l.starts_with("The"));
        ASSERT_TRUE(l.ends_with("Furs"));
        ASSERT_FALSE(l.starts_with("the"));
        ASSERT_FALSE(l.ends_with("furs"));
        ASSERT_TRUE(l.contains(""));
        ASSERT_TRUE(l.contains('d'));
        ASSERT_FALSE(l.contains('Z'));
        ASSERT_TRUE(l.contains("delic"));
        ASSERT_FALSE(l.contains("dElic"));
        ASSERT_TRUE(l.contains("The Psychedelic Furs"));
        ASSERT_FALSE(l.contains("The Psychedelic Furs+The Sisters of Mercy"));

        r = "The Sisters of Mercy";
        ASSERT_FALSE(l == r);
        ASSERT_TRUE(r.starts_with("The"));
        ASSERT_TRUE(r.ends_with("Mercy"));
        ASSERT_FALSE(l.starts_with("the"));
        ASSERT_FALSE(l.ends_with("mercy"));
    }
}
