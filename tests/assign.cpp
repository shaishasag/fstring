#include "gtest/gtest.h"
#include "fstring.h"

using namespace fstr;

/// Verify assignment to fstr::fstr_base of std::string, std::string_view, fstr::fstr_base
TEST(AssignTests, AssignObjects)
{
    const std::string std_postfix("!?");
    const std::string_view view_postfix("++");
    {
        fstr::fstr31 fs1("Julian Cope");
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
        fstr::fstr31 fs1("Julian Cope");
        EXPECT_STREQ(fs1.c_str(), "Julian Cope");
        fstr::fstr63 fixed_63("The Teardrop Explodes");
        EXPECT_STREQ(fixed_63.c_str(), "The Teardrop Explodes");

        fs1 = fixed_63;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes");
        fs1 += std_postfix;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes!?");
        fs1 += view_postfix;
        EXPECT_STREQ(fs1.c_str(), "The Teardrop Explodes!?++");

        fs1 = "Julian Cope";
        EXPECT_STREQ(fs1.c_str(), "Julian Cope");
        fstr::fstr_ref fixed_ref(fixed_63);
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
        fstr::fstr15 ms1 = "umaguma";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umaguma");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 7);

        fstr::fstr_ref ref1(ms1);

        if (ms1 == ref1) {
        }
        else if (ref1 == ms1) {
            
        }

        EXPECT_EQ(ms1, ref1);
    }
    {
        // simple construction by assignment
        fstr::fstr15 ms1 = "u";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "u");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 1);
    }
    {
        // assign char* to alread constructed
        fstr::fstr15 ms3("umaguma");
        ms3 = "Shinjuku";
        EXPECT_EQ(ms3.capacity(), 15);
        EXPECT_STREQ(ms3.c_str(), "Shinjuku");
        EXPECT_STRNE(ms3.c_str(), "umaguma");
        EXPECT_FALSE(ms3.empty());
        EXPECT_FALSE(ms3.full());
    }
    {
        // assign char* to alread constructed
        fstr15 ms4("umaguma");
        ms4 = "S";
        EXPECT_EQ(ms4.capacity(), 15);
        EXPECT_STREQ(ms4.c_str(), "S");
        EXPECT_STRNE(ms4.c_str(), "umaguma");
        EXPECT_FALSE(ms4.empty());
        EXPECT_FALSE(ms4.full());
        EXPECT_EQ(ms4.size(), 1);
    }
}

/// verify fstr::fstr_base::operator+=
TEST(AssignTests, AdditionTypeAssign)
{
    {
        // += char*
        fstr15 ms1 = "umag";
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
        fstr15 ms1 = "umag";
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
        fstr15 ms1;
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
        fstr15 ms1("quizzifications");
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
        fstr15 ms1("quizzifications");
        ms1 += 'S'; // adding another char is beyond fstr15 capacity
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "quizzifications");
        EXPECT_STRNE(ms1.c_str(), "quizzificationsS");
        EXPECT_FALSE(ms1.empty());
        EXPECT_TRUE(ms1.full());
        EXPECT_EQ(ms1.size(), 15);
    }
    {
        // simple too much: += char*
        fstr15 ms1 = "umaguma";
        ms1 += "BLEACHERS"; // last S is beyond fstr15 capacity
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umagumaBLEACHER");
        EXPECT_STRNE(ms1.c_str(), "umagumaBLEACHERS");
        EXPECT_FALSE(ms1.empty());
        EXPECT_TRUE(ms1.full());
        EXPECT_EQ(ms1.size(), 15);
    }
}

/// Verify assignment of empty char*, and fstr::fstr_base::clear
TEST(AssignTests, ClearAndEmptyAssign)
{
    {
        // assignment empty to empty
        fstr15 ms1;
        ms1 = "";
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "");
        EXPECT_TRUE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 0);
    }
    {
        // assignment empty to full
        fstr15 ms1 = "umaguma";
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
        fstr15 ms1 = "umaguma";
        ms1.clear();
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "");
        EXPECT_STRNE(ms1.c_str(), "umaguma");
        EXPECT_TRUE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 0);
    }
}

/// verufy std::swap onnfstr::fstr_base's
TEST(AssignTests, Swap)
{
    {   // swap same size fstring
        fstr::fstr31 a("Herbivore");
        fstr::fstr31 b("Carnivore");
        std::swap(a, b);
        EXPECT_STREQ(a.c_str(), "Carnivore");
        EXPECT_STREQ(b.c_str(), "Herbivore");
        std::swap(b, a);  // swap again
        EXPECT_STREQ(b.c_str(), "Carnivore");
        EXPECT_STREQ(a.c_str(), "Herbivore");
    }
    {   // swap different size fstring
        fstr::fstr31 a("Herbivore");
        fstr::fstr31 b("Carni");
        std::swap(a, b);
        EXPECT_STREQ(a.c_str(), "Carni");
        EXPECT_STREQ(b.c_str(), "Herbivore");
        std::swap(b, a);  // swap again
        EXPECT_STREQ(b.c_str(), "Carni");
        EXPECT_STREQ(a.c_str(), "Herbivore");
    }
    {   // swap with empty fstring
        fstr::fstr31 a("Herbivore");
        fstr::fstr31 b("Carni");
        b.clear();
        std::swap(a, b);
        EXPECT_STREQ(a.c_str(), "");
        EXPECT_STREQ(b.c_str(), "Herbivore");
        std::swap(b, a);  // swap again
        EXPECT_STREQ(b.c_str(), "");
        EXPECT_STREQ(a.c_str(), "Herbivore");
    }
}

/// Verify assign to fstr::fstr_ref effects the target fstr::fstr_base
TEST(AssignTests, AssignToRef)
{
    {
        fstr::fstr31 the_referred;
        fstr::fstr_ref the_ref(the_referred);

        the_ref = 'O';  // assign single char
        EXPECT_STREQ(the_referred.c_str(), "O");
        EXPECT_STREQ(the_ref.c_str(), "O");

        the_ref = "Herbivore";  // assign char*
        EXPECT_STREQ(the_referred.c_str(), "Herbivore");
        EXPECT_STREQ(the_ref.c_str(), "Herbivore");

        fstr::fstr15 f15{"Carnivore"};
        the_ref = f15;   // assign fstring
        EXPECT_STREQ(the_referred.c_str(), "Carnivore");
        EXPECT_STREQ(the_ref.c_str(), "Carnivore");

        fstr::fstr63 f63{"Omnivore"};
        fstr::fstr_ref f63_ref(f63);
        the_ref = f63_ref;   // assign fstr_ref
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

fstr::fstr_ref return_me_the_ref(fstr::fstr_ref the_ref)
{
    return the_ref;
}

/// Verify assign of reference to fstr_ref to fstr_ref
/// including through function calls, still refers to the original string
TEST(AssignTests, Ref2Ref2Ref)
{
    fstr::fstr31 original_str{"Detritivore"};
    fstr::fstr_ref ref1{original_str};
    EXPECT_STREQ(ref1.c_str(), "Detritivore");
    
    fstr::fstr_ref ref2{ref1};
    
    fstr::fstr_ref ref3 = return_me_the_ref(ref2);
    original_str += "1";  // change the original string directly
    ref2 += "2"; // change the through ref2
    ref3 += "3"; // change the through ref3
    
    // all refer to str so should have the same value
    EXPECT_STREQ(original_str.c_str(), "Detritivore123");
    EXPECT_STREQ(ref1.c_str(), "Detritivore123");
    EXPECT_STREQ(ref2.c_str(), "Detritivore123");
    EXPECT_STREQ(ref3.c_str(), "Detritivore123");
}
