#include "gtest/gtest.h"
#include "fstring.h"

using namespace fixed;

/// Verify assignment to fixed::fstring of std::string, std::string_view, fixed::fstring
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

/// Verify construction by assignment
TEST(AssignTests, ConstructAssign)
{
    {
        // construction by assignment of char*
        fixed::fstring15 ms1 = "umaguma";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umaguma");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 7);

        fixed::fstring_ref ref1(ms1);
        EXPECT_EQ(ms1, ref1);
    }
    {
        // simple construction by assignment
        fixed::fstring15 ms1 = "u";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "u");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 1);
    }
    {
        // assign char* to alread constructed
        fixed::fstring15 ms3("umaguma");
        ms3 = "Shinjuku";
        EXPECT_EQ(ms3.capacity(), 15);
        EXPECT_STREQ(ms3.c_str(), "Shinjuku");
        EXPECT_STRNE(ms3.c_str(), "umaguma");
        EXPECT_FALSE(ms3.empty());
        EXPECT_FALSE(ms3.full());
    }
    {
        // assign char* to alread constructed
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

/// verify fixed::fstring::operator+=
TEST(AssignTests, AdditionTypeAssign)
{
    {
        // += char*
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
        // += char
        fstring15 ms1 = "umag";
        ms1 += 'u';
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
        //  add char* to full fstring
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
        //  add char to full fstring
        fstring15 ms1("quizzifications");
        ms1 += 'S'; // adding another char is beyond fstring15 capacity
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "quizzifications");
        EXPECT_STRNE(ms1.c_str(), "quizzificationsS");
        EXPECT_FALSE(ms1.empty());
        EXPECT_TRUE(ms1.full());
        EXPECT_EQ(ms1.size(), 15);
    }
    {
        // simple too much: += char*
        fstring15 ms1 = "umaguma";
        ms1 += "BLEACHERS"; // last S is beyond fstring15 capacity
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umagumaBLEACHER");
        EXPECT_STRNE(ms1.c_str(), "umagumaBLEACHERS");
        EXPECT_FALSE(ms1.empty());
        EXPECT_TRUE(ms1.full());
        EXPECT_EQ(ms1.size(), 15);
    }
}

/// Verify assignment of empty char*, and fixed::fstring::clear
TEST(AssignTests, ClearAndEmptyAssign)
{
    {
        // assignment empty to empty
        fstring15 ms1;
        ms1 = "";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "");
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

/// verufy std::swap onnfixed::fstring's
TEST(AssignTests, Swap)
{
    {   // swap same size fstring
        fixed::fstring31 a("Herbivore");
        fixed::fstring31 b("Carnivore");
        std::swap(a, b);
        EXPECT_STREQ(a.c_str(), "Carnivore");
        EXPECT_STREQ(b.c_str(), "Herbivore");
        std::swap(b, a);  // swap again
        EXPECT_STREQ(b.c_str(), "Carnivore");
        EXPECT_STREQ(a.c_str(), "Herbivore");
    }
    {   // swap different size fstring
        fixed::fstring31 a("Herbivore");
        fixed::fstring31 b("Carni");
        std::swap(a, b);
        EXPECT_STREQ(a.c_str(), "Carni");
        EXPECT_STREQ(b.c_str(), "Herbivore");
        std::swap(b, a);  // swap again
        EXPECT_STREQ(b.c_str(), "Carni");
        EXPECT_STREQ(a.c_str(), "Herbivore");
    }
    {   // swap with empty fstring
        fixed::fstring31 a("Herbivore");
        fixed::fstring31 b("Carni");
        b.clear();
        std::swap(a, b);
        EXPECT_STREQ(a.c_str(), "");
        EXPECT_STREQ(b.c_str(), "Herbivore");
        std::swap(b, a);  // swap again
        EXPECT_STREQ(b.c_str(), "");
        EXPECT_STREQ(a.c_str(), "Herbivore");
    }
}

/// Verify assign to fixed::fstring_ref effects the target fixed::fstring
TEST(AssignTests, AssignToRef)
{
    {
        fixed::fstring31 the_referred;
        fixed::fstring_ref the_ref(the_referred);

        the_ref = 'O';  // assign single char
        EXPECT_STREQ(the_referred.c_str(), "O");
        EXPECT_STREQ(the_ref.c_str(), "O");

        the_ref = "Herbivore";  // assign char*
        EXPECT_STREQ(the_referred.c_str(), "Herbivore");
        EXPECT_STREQ(the_ref.c_str(), "Herbivore");

        fixed::fstring15 f15{"Carnivore"};
        the_ref = f15;   // assign fstring
        EXPECT_STREQ(the_referred.c_str(), "Carnivore");
        EXPECT_STREQ(the_ref.c_str(), "Carnivore");

        fixed::fstring63 f63{"Omnivore"};
        fixed::fstring_ref f63_ref(f63);
        the_ref = f63_ref;   // assign fstring_ref
        EXPECT_STREQ(the_referred.c_str(), "Omnivore");
        EXPECT_STREQ(the_ref.c_str(), "Omnivore");

        std::string_view d{"Felicity"};
        the_ref = d;  // assign std::string_view
        EXPECT_STREQ(the_referred.c_str(), "Felicity");
        EXPECT_STREQ(the_ref.c_str(), "Felicity");

        std::string e{"Porter"};
        the_ref = e;  // assign std::string
        EXPECT_STREQ(the_referred.c_str(), "Porter");
        EXPECT_STREQ(the_ref.c_str(), "Porter");
    }
}

fixed::fstring_ref return_me_the_ref(fixed::fstring_ref the_ref)
{
    return the_ref;
}

/// Verify assign of reference to fstring_ref to fstring_ref
/// including through function calls, still refers to the original string
TEST(AssignTests, Ref2Ref2Ref)
{
    fixed::fstring31 original_str{"Detritivore"};
    fixed::fstring_ref ref1{original_str};
    EXPECT_STREQ(ref1.c_str(), "Detritivore");
    
    fixed::fstring_ref ref2{ref1};
    
    fixed::fstring_ref ref3 = return_me_the_ref(ref2);
    original_str += "1";  // change the original string directly
    ref2 += "2"; // change the through ref2
    ref3 += "3"; // change the through ref3
    
    // all refer to str so should have the same value
    EXPECT_STREQ(original_str.c_str(), "Detritivore123");
    EXPECT_STREQ(ref1.c_str(), "Detritivore123");
    EXPECT_STREQ(ref2.c_str(), "Detritivore123");
    EXPECT_STREQ(ref3.c_str(), "Detritivore123");
}

#if 0
TEST(AssignTests, RepeatedAssignToRef)
{
    fixed::fstring15 f1{"Insectivore"};
    fixed::fstring15 f2{"Frugivore"};
    fixed::fstring15 f3{"Granivore"};
    
    fixed::fstring_ref the_ref{f1};
    EXPECT_STREQ(the_ref.c_str(), "Insectivore");
    EXPECT_STREQ(f1.c_str(), "Insectivore");
    EXPECT_STREQ(f2.c_str(), "Frugivore");
    EXPECT_STREQ(f2.c_str(), "Granivore");

    the_ref = f2;
    EXPECT_STREQ(the_ref.c_str(), "Frugivore");
    EXPECT_STREQ(f1.c_str(), "Frugivore");
    EXPECT_STREQ(f2.c_str(), "Frugivore");
    EXPECT_STREQ(f2.c_str(), "Granivore");

    the_ref = f3;
    EXPECT_STREQ(the_ref.c_str(), "Granivore");
    EXPECT_STREQ(f1.c_str(), "Frugivore");
    EXPECT_STREQ(f2.c_str(), "Frugivore");
    EXPECT_STREQ(f2.c_str(), "Frugivore");
}
#endif
