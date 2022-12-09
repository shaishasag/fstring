#include "gtest/gtest.h"
#include "fstring.h"

TEST(BasicTests, ObjectSize)
{
    ASSERT_EQ(sizeof(fixed::fstring_ref), 8);
    ASSERT_EQ(sizeof(fixed::fstring7), 24);
    ASSERT_EQ(sizeof(fixed::fstring15), 32);
    ASSERT_EQ(sizeof(fixed::fstring31), 48);
    ASSERT_EQ(sizeof(fixed::fstring63), 80);
}

TEST(ConstructionTests, char_ptr_Construction)
{
    {
        // simple construction
        fixed::fstring15 ms1("umaguma");
        EXPECT_EQ(ms1.capacity(), 15);
        EXPECT_STREQ(ms1.c_str(), "umaguma");
        EXPECT_STRNE(ms1.c_str(), "umaguma?");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 7);
    }
    {
        // empty construction
        fixed::fstring15 ms2("");
        EXPECT_EQ(ms2.capacity(), 15);
        EXPECT_STREQ(ms2.c_str(), "");
        EXPECT_STRNE(ms2.c_str(), "?");
        EXPECT_TRUE(ms2.empty());
        EXPECT_FALSE(ms2.full());
        EXPECT_EQ(ms2.size(), 0);
    }
    {
        // default construction
        fixed::fstring15 ms3;
        EXPECT_EQ(ms3.capacity(), 15);
        EXPECT_STREQ(ms3.c_str(), "");
        EXPECT_STRNE(ms3.c_str(), "?");
        EXPECT_TRUE(ms3.empty());
        EXPECT_FALSE(ms3.full());
        EXPECT_EQ(ms3.size(), 0);
    }
    {
        // exact capacity construction
        fixed::fstring15 ms4("umaguma is actu");
        EXPECT_EQ(ms4.capacity(), 15);
        EXPECT_STREQ(ms4.c_str(), "umaguma is actu");
        EXPECT_STRNE(ms4.c_str(), "umaguma is actually spelled Ummagumma");
        EXPECT_FALSE(ms4.empty());
        EXPECT_TRUE(ms4.full());
        EXPECT_EQ(ms4.size(), 15);
    }
    {
        // over capacity construction
        fixed::fstring15 ms5("umaguma is actually spelled Ummagumma");
        EXPECT_EQ(ms5.capacity(), 15);
        EXPECT_STREQ(ms5.c_str(), "umaguma is actu");
        EXPECT_STRNE(ms5.c_str(), "umaguma is actually spelled Ummagumma");
        EXPECT_FALSE(ms5.empty());
        EXPECT_TRUE(ms5.full());
        EXPECT_EQ(ms5.size(), 15);
    }
#if 0
    {
        // by size construction - exact
        fixed::fstring15 ms6("umaguma is actually spelled Ummagumma", 7);
        EXPECT_EQ(ms6.capacity(), 15);
        EXPECT_STREQ(ms6.c_str(), "umaguma");
        EXPECT_STRNE(ms6.c_str(), "umaguma is actually spelled Ummagumma");
        EXPECT_FALSE(ms6.empty());
        EXPECT_FALSE(ms6.full());
        EXPECT_EQ(ms6.size(), 7);
    }
    {
        // by size construction - too short
        fixed::fstring15 ms7("umaguma", 3);
        EXPECT_EQ(ms7.capacity(), 15);
        EXPECT_STREQ(ms7.c_str(), "uma");
        EXPECT_STRNE(ms7.c_str(), "umaguma");
        EXPECT_FALSE(ms7.empty());
        EXPECT_FALSE(ms7.full());
        EXPECT_EQ(ms7.size(), 3);
    }
#endif
}


TEST(ConstructionTests, CopyConstruction1)
{
    {
        // simple construction
        fixed::fstring15 ms1("umaguma");
        fixed::fstring15 copyms1(ms1);
        EXPECT_EQ(copyms1.capacity(), 15);
        EXPECT_STREQ(copyms1.c_str(), "umaguma");
        EXPECT_STRNE(copyms1.c_str(), "umaguma?");
        EXPECT_FALSE(copyms1.empty());
        EXPECT_FALSE(copyms1.full());
        EXPECT_EQ(copyms1.size(), 7);
    }
    {
        // empty construction
        fixed::fstring15 ms2("");
        fixed::fstring15 copyms2(ms2);
        EXPECT_EQ(copyms2.capacity(), 15);
        EXPECT_STREQ(copyms2.c_str(), "");
        EXPECT_STRNE(copyms2.c_str(), "?");
        EXPECT_TRUE(copyms2.empty());
        EXPECT_FALSE(copyms2.full());
        EXPECT_EQ(copyms2.size(), 0);
    }
    {

        // default construction
        fixed::fstring15 ms3;
        fixed::fstring15 copyms3(ms3);
        EXPECT_EQ(copyms3.capacity(), 15);
        EXPECT_STREQ(copyms3.c_str(), "");
        EXPECT_STRNE(copyms3.c_str(), "?");
        EXPECT_TRUE(copyms3.empty());
        EXPECT_FALSE(copyms3.full());
        EXPECT_EQ(copyms3.size(), 0);
    }
    {
        // exact capacity construction
        fixed::fstring15 ms4("umaguma is actu");
        fixed::fstring15 copyms4(ms4);
        EXPECT_EQ(copyms4.capacity(), 15);
        EXPECT_STREQ(copyms4.c_str(), "umaguma is actu");
        EXPECT_STRNE(copyms4.c_str(), "umaguma is actually spelled Ummagumma");
        EXPECT_FALSE(copyms4.empty());
        EXPECT_TRUE(copyms4.full());
        EXPECT_EQ(copyms4.size(), 15);
    }
    {
        // over capacity construction
        fixed::fstring15 ms5("umaguma is actually spelled Ummagumma");
        fixed::fstring15 copyms5(ms5);
        EXPECT_EQ(copyms5.capacity(), 15);
        EXPECT_STREQ(copyms5.c_str(), "umaguma is actu");
        EXPECT_STRNE(copyms5.c_str(), "umaguma is actually spelled Ummagumma");
        EXPECT_FALSE(copyms5.empty());
        EXPECT_TRUE(copyms5.full());
        EXPECT_EQ(copyms5.size(), 15);
    }
#if 0
    {
        // by size construction - exact
        fixed::fstring15 ms6("umaguma is actually spelled Ummagumma", 7);
        fixed::fstring15 copyms6(ms6);
        EXPECT_EQ(copyms6.capacity(), 15);
        EXPECT_STREQ(copyms6.c_str(), "umaguma");
        EXPECT_STRNE(copyms6.c_str(), "umaguma is actually spelled Ummagumma");
        EXPECT_FALSE(copyms6.empty());
        EXPECT_FALSE(copyms6.full());
        EXPECT_EQ(copyms6.size(), 7);
    }
    {
        // by size construction - too short
        fixed::fstring15 ms7("umaguma", 3);
        fixed::fstring15 copyms7(ms7);
        EXPECT_EQ(copyms7.capacity(), 15);
        EXPECT_STREQ(copyms7.c_str(), "uma");
        EXPECT_STRNE(copyms7.c_str(), "umaguma");
        EXPECT_FALSE(copyms7.empty());
        EXPECT_FALSE(copyms7.full());
        EXPECT_EQ(copyms7.size(), 3);
    }
#endif
}


TEST(ConstructionTests, RefConstruction)
{
    {
        // simple construction
        fixed::fstring15 ms1("umaguma");
        fixed::fstring_ref refms1(ms1);
        EXPECT_EQ(refms1.capacity(), 15);
        EXPECT_STREQ(refms1.c_str(), "umaguma");
        EXPECT_STRNE(refms1.c_str(), "umaguma?");
        EXPECT_FALSE(refms1.empty());
        EXPECT_FALSE(refms1.full());
        EXPECT_EQ(refms1.size(), 7);
    }
    {
        // empty construction
        fixed::fstring15 ms2("");
        fixed::fstring_ref refms2(ms2);
        EXPECT_EQ(refms2.capacity(), 15);
        EXPECT_STREQ(refms2.c_str(), "");
        EXPECT_STRNE(refms2.c_str(), "?");
        EXPECT_TRUE(refms2.empty());
        EXPECT_FALSE(refms2.full());
        EXPECT_EQ(refms2.size(), 0);
    }
    {
        // default construction
        fixed::fstring15 ms3;
        fixed::fstring_ref refms3(ms3);
        EXPECT_EQ(refms3.capacity(), 15);
        EXPECT_STREQ(refms3.c_str(), "");
        EXPECT_STRNE(refms3.c_str(), "?");
        EXPECT_TRUE(refms3.empty());
        EXPECT_FALSE(refms3.full());
        EXPECT_EQ(refms3.size(), 0);
    }
    {
        // exact capacity construction
        fixed::fstring15 ms4("umaguma is actu");
        fixed::fstring_ref refms4(ms4);
        EXPECT_EQ(refms4.capacity(), 15);
        EXPECT_STREQ(refms4.c_str(), "umaguma is actu");
        EXPECT_STRNE(refms4.c_str(), "umaguma is actually spelled Ummagumma");
        EXPECT_FALSE(refms4.empty());
        EXPECT_TRUE(refms4.full());
        EXPECT_EQ(refms4.size(), 15);
    }
    {
        // over capacity construction
        fixed::fstring15 ms5("umaguma is actually spelled Ummagumma");
        fixed::fstring_ref refms5(ms5);
        EXPECT_EQ(refms5.capacity(), 15);
        EXPECT_STREQ(refms5.c_str(), "umaguma is actu");
        EXPECT_STRNE(refms5.c_str(), "umaguma is actually spelled Ummagumma");
        EXPECT_FALSE(refms5.empty());
        EXPECT_TRUE(refms5.full());
        EXPECT_EQ(refms5.size(), 15);
    }
#if 0
    {
        // by size construction - exact
        fixed::fstring15 ms6("umaguma is actually spelled Ummagumma", 7);
        fixed::fstring_ref refms6(ms6);
        EXPECT_EQ(refms6.capacity(), 15);
        EXPECT_STREQ(refms6.c_str(), "umaguma");
        EXPECT_STRNE(refms6.c_str(), "umaguma is actually spelled Ummagumma");
        EXPECT_FALSE(refms6.empty());
        EXPECT_FALSE(refms6.full());
        EXPECT_EQ(refms6.size(), 7);
    }
    {
        // by size construction - too short
        fixed::fstring15 ms7("umaguma", 3);
        fixed::fstring_ref refms7(ms7);
        EXPECT_EQ(refms7.capacity(), 15);
        EXPECT_STREQ(refms7.c_str(), "uma");
        EXPECT_STRNE(refms7.c_str(), "umaguma");
        EXPECT_FALSE(refms7.empty());
        EXPECT_FALSE(refms7.full());
        EXPECT_EQ(refms7.size(), 3);
    }
#endif
}

TEST(ConstructionTests, CopyConstruction2)
{
    {
        // cop construction from smaller size
        fixed::fstring15 ms("umaguma");
        fixed::fstring31 ms1(ms);
        EXPECT_EQ(ms1.capacity(), 31);
        EXPECT_STREQ(ms1.c_str(), "umaguma");
        EXPECT_STRNE(ms1.c_str(), "umaguma?");
        EXPECT_FALSE(ms1.empty());
        EXPECT_FALSE(ms1.full());
        EXPECT_EQ(ms1.size(), 7);
    }
    {
        // cop construction from bigger size
        fixed::fstring15 ms("Ummagumma");
        fixed::fstring7 ms1(ms);
        EXPECT_EQ(ms1.capacity(), 7);
        EXPECT_STREQ(ms1.c_str(), "Ummagum");
        EXPECT_STRNE(ms1.c_str(), "Ummagumma");
        EXPECT_FALSE(ms1.empty());
        EXPECT_TRUE(ms1.full());
        EXPECT_EQ(ms1.size(), 7);
    }
}
