#include "gtest/gtest.h"
#include "fstring.h"

using namespace fixed;

TEST(AssignTests, AssignObjects)
{
    const std::string std_postfix("!?");
    const std::string_view view_postfix("++");
    {
        fixed::fstring31 fs1("Julian Cope");
        EXPECT_STREQ(fs1.c_str(), "Julian Cope");

        std::string std_s("The Teardrop Explodes");
        fs1 = std_s;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes");
        fs1 += std_postfix;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes!?");
        fs1 += view_postfix;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes!?++");

        fs1 = "Julian Cope";
        EXPECT_STREQ(fs1.c_str(), "Julian Cope");
        std::string_view std_sv(std_s);
        fs1 = std_sv;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes");
    }
    {
        fixed::fstring31 fs1("Julian Cope");
        EXPECT_STREQ(fs1.c_str(), "Julian Cope");
        fixed::fstring63 fixed_63("The Teardrop Explodes");
        EXPECT_STREQ(fixed_63.c_str(), "The Teardrop Explodes");

        fs1 = fixed_63;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes");
        fs1 += std_postfix;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes!?");
        fs1 += view_postfix;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes!?++");

        fs1 = "Julian Cope";
        EXPECT_STREQ(fs1.c_str(), "Julian Cope");
        fixed::fstring_ref fixed_ref(fixed_63);
        fs1 = fixed_ref;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes");
        fs1 += std_postfix;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes!?");
        fs1 += view_postfix;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes!?++");
    }
}

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

TEST(AssignTests, Swap)
{
    {   // swap same size fstring
        fixed::fstring31 a("Herbivore");
        fixed::fstring31 b("Carnivore");
        std::swap(a, b);
        EXPECT_STREQ(a.c_str(), "Carnivore");
        EXPECT_STREQ(b.c_str(), "Herbivore");
    }
#if 0
    {   // swap same size fstring_ref
        fixed::fstring31 a("Herbivore");
        fixed::fstring31 b("Carnivore");

        fixed::fstring_ref a_ref(a);
        fixed::fstring_ref b_ref(b);
        std::swap(a_ref, b_ref);

        EXPECT_STREQ(a_ref.c_str(), "Carnivore");
        EXPECT_STREQ(b_ref.c_str(), "Herbivore");
    }
    {   // swap different size fstring
        fixed::fstring31 a("Herbivore");
        fixed::fstring15 b("Carnivore");
        std::swap(a, b);
        EXPECT_STREQ(a.c_str(), "Carnivore");
        EXPECT_STREQ(b.c_str(), "Herbivore");
    }
#endif
}
