#include "gtest/gtest.h"
#include "fstring.h"

TEST(EraseTests, IndexNoCount)
{
    {
        // erase it all
        fixed::fstring31 s("Pump up the Volume");
        s.erase((unsigned)0);
        EXPECT_TRUE(s.empty());
    }
    {
        // erase some
        fixed::fstring31 s("Pump up the Volume");
        s.erase((unsigned)7);
        EXPECT_STREQ(s.c_str(), "Pump up");
    }
    {
        // erase the end
        fixed::fstring31 s("Pump up the Volume");
        s.erase((unsigned)18);
        EXPECT_STREQ(s.c_str(), "Pump up the Volume");
    }
    {
        // erase too far
        EXPECT_THROW({
            fixed::fstring31 s("Pump up the Volume");
            s.erase((unsigned)19);
        }, std::out_of_range );
    }
}

TEST(EraseTests, IndexWithCount)
{
    {
        // erase from start
        fixed::fstring31 s("Pump up the Volume");
        s.erase((unsigned)0, 5);
        EXPECT_STREQ(s.c_str(), "up the Volume");
    }
    {
        // erase from middle
        fixed::fstring31 s("Pump up the Volume");
        s.erase((unsigned)8, 4);
        EXPECT_STREQ(s.c_str(), "Pump up Volume");
    }
    {
        // erase the end
        fixed::fstring31 s("Pump up the Volume");
        s.erase((unsigned)11, 9);
        EXPECT_STREQ(s.c_str(), "Pump up the");
    }
    {
        // erase too far
        EXPECT_THROW({
            fixed::fstring31 s("Pump up the Volume");
            s.erase((unsigned)19, 2);
        }, std::out_of_range );
    }
}

TEST(EraseTests, Range)
{
    {
        // erase from start
        fixed::fstring31 s("Pump up the Volume");
        auto p = s.erase(s.begin(), s.begin()+5);
        EXPECT_STREQ(s.c_str(), "up the Volume");
        EXPECT_STREQ(p, "up the Volume");
    }
    {
        // erase from middle
        fixed::fstring31 s("Pump up the Volume");
        auto p = s.erase(s.begin()+8, s.begin()+8+4);
        EXPECT_STREQ(s.c_str(), "Pump up Volume");
        EXPECT_STREQ(p, "Volume");
    }
    {
        // erase the end
        fixed::fstring31 s("Pump up the Volume");
        auto p = s.erase(s.begin()+11, s.begin()+11+9);
        EXPECT_STREQ(s.c_str(), "Pump up the");
        EXPECT_EQ(s.end(), p);
    }
}

TEST(EraseTests, OneWithPtr)
{
    {
        // erase from start
        fixed::fstring31 s("Pump up the Volume");
        auto p = s.erase(s.begin());
        EXPECT_STREQ(s.c_str(), "ump up the Volume");
        EXPECT_STREQ(p, "ump up the Volume");
    }
    {
        // erase from middle
        fixed::fstring31 s("Pump up the Volume");
        auto p = s.erase(s.begin()+8);
        EXPECT_STREQ(s.c_str(), "Pump up he Volume");
        EXPECT_STREQ(p, "he Volume");
    }
    {
        // erase the end
        fixed::fstring31 s("Pump up the Volume");
        auto p = s.erase(s.begin()+17);
        EXPECT_STREQ(s.c_str(), "Pump up the Volum");
        EXPECT_EQ(p, s.end());
    }
}


TEST(EraseTests, PopBack)
{
    {
        fixed::fstring31 s("Pump up the Volume");
        s.pop_back();
        EXPECT_STREQ(s.c_str(), "Pump up the Volum");
    }
}
