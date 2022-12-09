#include "gtest/gtest.h"
#include "fstring.h"

TEST(Trim, trim_simple)
{
    {   // trim empty string
        fixed::fstring31 empty;
        empty.trim_front();
        empty.trim_back();
        EXPECT_STREQ(empty.c_str(), "");
        EXPECT_TRUE(empty.empty());
        EXPECT_FALSE(empty.full());
        EXPECT_EQ(empty.size(), 0);
    }
    {   // trim a string that does not nedd trimming
        fixed::fstring31 con("Kajagoogoo");
        con.trim_front();
        con.trim_back();
        EXPECT_STREQ(con.c_str(), "Kajagoogoo");
        EXPECT_STRNE(con.c_str(), "ajagoogoo");
        EXPECT_FALSE(con.empty());
        EXPECT_FALSE(con.full());
        EXPECT_EQ(con.size(), 10);
    }
    {   // trip front spaces
        fixed::fstring31 con(" Kajagoogoo");
        con.trim_front();
        EXPECT_STREQ(con.c_str(), "Kajagoogoo");
        EXPECT_STRNE(con.c_str(), " Kajagoogoo");
        EXPECT_FALSE(con.empty());
        EXPECT_FALSE(con.full());
        EXPECT_EQ(con.size(), 10);
    }
    {   // trim back spaces
        fixed::fstring31 con("Kajagoogoo ");
        con.trim_back();
        EXPECT_STREQ(con.c_str(), "Kajagoogoo");
        EXPECT_STRNE(con.c_str(), "Kajagoogoo ");
        EXPECT_FALSE(con.empty());
        EXPECT_FALSE(con.full());
        EXPECT_EQ(con.size(), 10);
    }
    {   // trim_front() & trim_back()
        fixed::fstring31 con(" \t Kajagoogoo \r ");
        con.trim_back();
        con.trim_front();
        EXPECT_STREQ(con.c_str(), "Kajagoogoo");
        EXPECT_STRNE(con.c_str(), " \t Kajagoogoo \r ");
        EXPECT_FALSE(con.empty());
        EXPECT_FALSE(con.full());
        EXPECT_EQ(con.size(), 10);
    }
    {   // trim all spaces using trim()
        fixed::fstring31 con(" \t Kajagoogoo \r ");
        con.trim();
        EXPECT_STREQ(con.c_str(), "Kajagoogoo");
        EXPECT_STRNE(con.c_str(), " \t Kajagoogoo \r ");
        EXPECT_FALSE(con.empty());
        EXPECT_FALSE(con.full());
        EXPECT_EQ(con.size(), 10);
    }
}

TEST(Trim, trim_with_reference)
{
    {   // trim empty string
        fixed::fstring31 empty;
        fixed::fstring_ref ref(empty);
        ref.trim_front();
        ref.trim_back();
        EXPECT_STREQ(ref.c_str(), "");
        EXPECT_TRUE(ref.empty());
        EXPECT_FALSE(ref.full());
        EXPECT_EQ(ref.size(), 0);
    }
    {   // trim a string that does not nedd trimming
        fixed::fstring31 con("Kajagoogoo");
        fixed::fstring_ref ref(con);
        ref.trim_front();
        ref.trim_back();
        EXPECT_STREQ(ref.c_str(), "Kajagoogoo");
        EXPECT_STRNE(ref.c_str(), "ajagoogoo");
        EXPECT_FALSE(ref.empty());
        EXPECT_FALSE(ref.full());
        EXPECT_EQ(ref.size(), 10);
    }
    {   // trip front spaces
        fixed::fstring31 con(" Kajagoogoo");
        fixed::fstring_ref ref(con);
        ref.trim_front();
        EXPECT_STREQ(ref.c_str(), "Kajagoogoo");
        EXPECT_STRNE(ref.c_str(), " Kajagoogoo");
        EXPECT_FALSE(ref.empty());
        EXPECT_FALSE(ref.full());
        EXPECT_EQ(ref.size(), 10);
    }
    {   // trim back spaces
        fixed::fstring31 con("Kajagoogoo ");
        fixed::fstring_ref ref(con);
        ref.trim_back();
        EXPECT_STREQ(ref.c_str(), "Kajagoogoo");
        EXPECT_STRNE(ref.c_str(), "Kajagoogoo ");
        EXPECT_FALSE(ref.empty());
        EXPECT_FALSE(ref.full());
        EXPECT_EQ(ref.size(), 10);
    }
    {   // trim_front() & trim_back()
        fixed::fstring31 con(" \t Kajagoogoo \r ");
        fixed::fstring_ref ref(con);
        ref.trim_back();
        ref.trim_front();
        EXPECT_STREQ(ref.c_str(), "Kajagoogoo");
        EXPECT_STRNE(ref.c_str(), " \t Kajagoogoo \r ");
        EXPECT_FALSE(ref.empty());
        EXPECT_FALSE(ref.full());
        EXPECT_EQ(ref.size(), 10);
    }
    {   // trim all spaces using trim()
        fixed::fstring31 con(" \t Kajagoogoo \r ");
        fixed::fstring_ref ref(con);
        ref.trim();
        EXPECT_STREQ(ref.c_str(), "Kajagoogoo");
        EXPECT_STRNE(ref.c_str(), " \t Kajagoogoo \r ");
        EXPECT_FALSE(ref.empty());
        EXPECT_FALSE(ref.full());
        EXPECT_EQ(ref.size(), 10);
    }
}
