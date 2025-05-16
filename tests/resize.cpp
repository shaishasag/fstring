#include "gtest/gtest.h"
#include "fstring.h"


TEST(Resize, resize)
{
    {   // resize of an empty string to 0
        fstr::fstr7 empty_fstr;
        EXPECT_EQ(empty_fstr.size(), 0);
    }
    {   // resize of an empty string to 1
        fstr::fstr7 empty_fstr;
        EXPECT_EQ(empty_fstr.size(), 0);
        empty_fstr.resize(1, 's');
        EXPECT_EQ(empty_fstr.size(), 1);
        EXPECT_EQ(empty_fstr[0], 's');

        empty_fstr.resize(0, 's'); // resize back to empty
        EXPECT_EQ(empty_fstr.size(), 0);
    }
    {   // resize of an empty string to full
        fstr::fstr7 empty_fstr;
        EXPECT_EQ(empty_fstr.size(), 0);
        empty_fstr.resize(7, 's');
        EXPECT_EQ(empty_fstr.size(), 7);
        EXPECT_EQ(empty_fstr, "sssssss");

        empty_fstr.resize(3, 'x'); // resize-down back
        EXPECT_EQ(empty_fstr.size(), 3);
        EXPECT_EQ(empty_fstr, "sss");
    }
    {   // resize of a full string to full
        fstr::fstr7 a_fstr("aaaaaaa");
        EXPECT_EQ(a_fstr.size(), 7);
        a_fstr.resize(7, 's');
        EXPECT_EQ(a_fstr.size(), 7);
        EXPECT_EQ(a_fstr, "aaaaaaa");

        a_fstr.resize(3, 'x'); // resize-down back
        EXPECT_EQ(a_fstr.size(), 3);
        EXPECT_EQ(a_fstr, "aaa");
    }
    {   // resize of an empty string to above full
        fstr::fstr7 empty_fstr;
        EXPECT_EQ(empty_fstr.size(), 0);
        ASSERT_THROW(empty_fstr.resize(17, 's'), std::length_error);
        EXPECT_EQ(empty_fstr.size(), 0); // empty_fstr shouod nt change
    }
    {   // resize of a string to above full
        fstr::fstr7 a_fstr("aaa");
        EXPECT_EQ(a_fstr.size(), 3);
        ASSERT_THROW(a_fstr.resize(17, 's'), std::length_error);
        EXPECT_EQ(a_fstr.size(), 3); // a_fstr shouod nt change
    }
}
