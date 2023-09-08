#include "gtest/gtest.h"
#include "fstring.h"
#include "fstringstream.h"
#include <string_view>
#include <mach/kern_return.h>

TEST(Stream, stream_numbers)
{
    {
        fixed::fstring127 fs;
        fs << true;
        EXPECT_STREQ(fs.c_str(), "true");
        fs << false;
        EXPECT_STREQ(fs.c_str(), "truefalse");

        fixed::fstring_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << true;
        EXPECT_STREQ(fs_ref.c_str(), "true");
        fs_ref << false;
        EXPECT_STREQ(fs_ref.c_str(), "truefalse");
    }
    {
        fixed::fstring127 fs;
        fs << 'z';
        EXPECT_STREQ(fs.c_str(), "z");

        fixed::fstring_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << 'z';
        EXPECT_STREQ(fs_ref.c_str(), "z");
    }
    {
        fixed::fstring127 fs;
        fs << 17;
        EXPECT_STREQ(fs.c_str(), "17");

        fixed::fstring_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << 17;
        EXPECT_STREQ(fs_ref.c_str(), "17");
    }
    {
        fixed::fstring127 fs;
        fs << 18446744073709551615U;
        EXPECT_STREQ(fs.c_str(), "18446744073709551615");

        fixed::fstring_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << 18446744073709551615U;
        EXPECT_STREQ(fs_ref.c_str(), "18446744073709551615");
    }
}

TEST(Stream, stream_strs)
{
    {
        fixed::fstring127 fs;
        fs << "Potassium";
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fixed::fstring_ref fs_ref(fs);
        fs_ref << "Potassium";
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fixed::fstring127 fs;
        fs << fixed::fstring15("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fixed::fstring_ref fs_ref(fs);
        fs_ref << fixed::fstring15("Potassium");
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fixed::fstring127 fs;
        fixed::fstring15 ps("Potassium");
        fs << fixed::fstring_ref(ps);
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fixed::fstring_ref fs_ref(fs);
        fs_ref << fixed::fstring_ref(ps);
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fixed::fstring127 fs;
        fs << std::string_view("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fixed::fstring_ref fs_ref(fs);
        fs_ref << std::string_view("Potassium");
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fixed::fstring127 fs;
        fs << std::string("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fixed::fstring_ref fs_ref(fs);
        fs_ref << std::string("Potassium");
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }

    {
        kern_return_t kernResult{18};
        bool b = std::is_convertible_v<decltype(kernResult), std::string_view>;
        EXPECT_FALSE(b);
        EXPECT_TRUE(std::is_integral_v<decltype(kernResult)>);

        fixed::fstring127 fs;
        fs << kernResult;
        EXPECT_STREQ(fs.c_str(), "18");
        fixed::fstring_ref fs_ref(fs);
        kernResult = 19;
        fs_ref << kernResult;
        EXPECT_STREQ(fs.c_str(), "1819");
    }

}
