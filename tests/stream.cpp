#include "gtest/gtest.h"
#include "fstring.h"
#include "fstringstream.h"

TEST(Stream, stream_numbers)
{
#if 0
    {
        fixed::fstring127 fs;
        fs << true;
        EXPECT_STREQ(fs.c_str(), "true");
        fs << false;
        EXPECT_STREQ(fs.c_str(), "truefalse");
    }
    {
        fixed::fstring127 fs;
        fs << 'z';
        EXPECT_STREQ(fs.c_str(), "z");
    }
    {
        fixed::fstring127 fs;
        fs << 17;
        EXPECT_STREQ(fs.c_str(), "17");
    }
    {
        fixed::fstring127 fs;
        fs << 18446744073709551615U;
        EXPECT_STREQ(fs.c_str(), "18446744073709551615");
    }
//    {
//        fixed::fstring127 fs;
//        fs << 17.0;
//        EXPECT_STREQ(fs.c_str(), "17.0");
//    }
#endif
}

TEST(Stream, stream_strs)
{
    {
        fixed::fstring127 fs;
        fs << "Potassium";
        EXPECT_STREQ(fs.c_str(), "Potassium");
    }
    {
        fixed::fstring127 fs;
        fs << fixed::fstring15("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");
    }
    {
        fixed::fstring127 fs;
        fixed::fstring15 ps("Potassium");
        fs << fixed::fstring_ref(ps);
        EXPECT_STREQ(fs.c_str(), "Potassium");
    }
    {
        fixed::fstring127 fs;
        fs << std::string_view("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");
    }
    {
        fixed::fstring127 fs;
        fs << std::string("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");
    }
}
