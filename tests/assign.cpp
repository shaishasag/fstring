#include "gtest/gtest.h"
#include "fstring.h"

using namespace fixed;

TEST(AssignTests, ConstructAssign)
{
    {
        // simple construction by assignment
        fixed::fstring15 ms1 = "umaguma";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umaguma");
        EXPECT_STRNE(ms1.c_str(), "umaguma?");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 7);

        fixed::fstring_ref ref1(ms1);
        EXPECT_EQ(ref1.capacity(), 15);
        EXPECT_STREQ(ref1.c_str(), "umaguma");
        EXPECT_STRNE(ref1.c_str(), "umaguma?");
        EXPECT_FALSE(ref1.empty());
        EXPECT_FALSE(ref1.full());
        EXPECT_EQ(ref1.size(), 7);
    }
    {
        // simple construction by assignment
        fixed::fstring15 ms1 = "u";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "u");
        EXPECT_STRNE(ms1.c_str(), "?");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 1);
    }
    {
        // assign to existing / char*
        fixed::fstring15 ms3("umaguma");
        ms3 = "Shinjuku";
        EXPECT_EQ(ms3.capacity(), 15);
        EXPECT_STREQ(ms3.c_str(), "Shinjuku");
        EXPECT_STRNE(ms3.c_str(), "umaguma");
        EXPECT_FALSE(ms3.empty());
        EXPECT_FALSE(ms3.full());
    }
    {
        // assign to existing / char
        fstring15 ms4("umaguma");
        ms4 = "S";
        EXPECT_EQ(ms4.capacity(), 15);
        EXPECT_STREQ(ms4.c_str(), "S");
        EXPECT_STRNE(ms4.c_str(), "umaguma");
        EXPECT_FALSE(ms4.empty());
        EXPECT_FALSE(ms4.full());
        EXPECT_EQ(ms4.size(), 1);
    }
}

TEST(AssignTests, AdditionTypeAssign)
{
    {
        // simple add / char*
        fstring15 ms1 = "umag";
        ms1 += "uma";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umaguma");
        EXPECT_STRNE(ms1.c_str(), "umag");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 7);
    }
    {
        // simple add / char
        fstring15 ms1 = "umag";
        ms1 += "u";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umagu");
        EXPECT_STRNE(ms1.c_str(), "umag");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 5);
    }

    {
        //  add to empty
        fstring15 ms1;
        ms1 += "umaguma";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umaguma");
        EXPECT_STRNE(ms1.c_str(), "");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 7);
    }
    {
        //  add to full / char*
        fstring15 ms1("quizzifications");
        ms1 += "umaguma";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "quizzifications");
        EXPECT_STRNE(ms1.c_str(), "quizzificationsumaguma");
        EXPECT_FALSE(ms1.empty());
        EXPECT_TRUE(ms1.full());
        EXPECT_EQ(ms1.size(), 15);
    }
    {
        //  add to full / char
        fstring15 ms1("quizzifications");
        ms1 += 'S';
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "quizzifications");
        EXPECT_STRNE(ms1.c_str(), "quizzificationsS");
        EXPECT_FALSE(ms1.empty());
        EXPECT_TRUE(ms1.full());
        EXPECT_EQ(ms1.size(), 15);
    }
    {
        // simple too much / char*
        fstring15 ms1 = "umaguma";
        ms1 += "BLEACHERS";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umagumaBLEACHER");
        EXPECT_STRNE(ms1.c_str(), "umagumaBLEACHERS");
        EXPECT_FALSE(ms1.empty());
        EXPECT_TRUE(ms1.full());
        EXPECT_EQ(ms1.size(), 15);
    }
}

TEST(AssignTests, ClearAndEmptyAssign)
{
    {
        // assignment empty to empty
        fstring15 ms1;
        ms1 = "";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "");
        EXPECT_STRNE(ms1.c_str(), "umaguma");
        EXPECT_TRUE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 0);
    }
    {
        // assignment empty to full
        fstring15 ms1 = "umaguma";
        ms1 = "";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "");
        EXPECT_STRNE(ms1.c_str(), "umaguma");
        EXPECT_TRUE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 0);
    }
    {
        // clear
        fstring15 ms1 = "umaguma";
        ms1.clear();
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "");
        EXPECT_STRNE(ms1.c_str(), "umaguma");
        EXPECT_TRUE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 0);
    }
}

TEST(AssignTests, RepeasedAssign)
{
    {
        // assignment empty to empty
        fstring15 ms1("umaguma");
        ms1.operator=("a");
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "a");
        EXPECT_STRNE(ms1.c_str(), "");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 1);
    }
}
