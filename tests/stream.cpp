#include "gtest/gtest.h"
#include "fstring.h"
#include "fstringstream.h"
#include <string_view>

TEST(Stream, stream_numbers)
{
    {
        fstr::fstr127 fs;
        fs << true;
        EXPECT_STREQ(fs.c_str(), "true");
        fs << false;
        EXPECT_STREQ(fs.c_str(), "truefalse");

        fstr::fstr_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << true;
        EXPECT_STREQ(fs_ref.c_str(), "true");
        fs_ref << false;
        EXPECT_STREQ(fs_ref.c_str(), "truefalse");
    }
    {
        fstr::fstr127 fs;
        fs << 'z';
        EXPECT_STREQ(fs.c_str(), "z");

        fstr::fstr_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << 'z';
        EXPECT_STREQ(fs_ref.c_str(), "z");
    }
    {
        fstr::fstr127 fs;
        fs << 17;
        EXPECT_STREQ(fs.c_str(), "17");

        fstr::fstr_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << 17;
        EXPECT_STREQ(fs_ref.c_str(), "17");
    }
    {
        fstr::fstr127 fs;
        fs << 18446744073709551615U;
        EXPECT_STREQ(fs.c_str(), "18446744073709551615");

        fstr::fstr_ref fs_ref(fs);
        fs_ref.clear();
        fs_ref << 18446744073709551615U;
        EXPECT_STREQ(fs_ref.c_str(), "18446744073709551615");
    }
}

TEST(Stream, stream_strs)
{
    {
        fstr::fstr127 fs;
        fs << "Potassium";
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << "Potassium";
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fstr::fstr127 fs;
        fs << fstr::fstr15("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << fstr::fstr15("Potassium");
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fstr::fstr127 fs;
        fstr::fstr15 ps("Potassium");
        fs << fstr::fstr_ref(ps);
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << fstr::fstr_ref(ps);
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fstr::fstr127 fs;
        fs << std::string_view("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << std::string_view("Potassium");
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
    {
        fstr::fstr127 fs;
        fs << std::string("Potassium");
        EXPECT_STREQ(fs.c_str(), "Potassium");

        fstr::fstr_ref fs_ref(fs);
        fs_ref << std::string("Potassium");
        EXPECT_STREQ(fs_ref.c_str(), "PotassiumPotassium");
    }
}

TEST(Stream, more_streaming)
{
    {   // stream to fstr with integer and boolean
        fstr::fstr31 vari;
        vari << "The" << ' ' << 3 << ' ' << "Musketeers? " << true;
        EXPECT_EQ(vari, "The 3 Musketeers? true");
    }
    {   // stream to fstr_ref with integer and boolean
        fstr::fstr31 vari;
        fstr::fstr_ref vari_ref{vari};
        vari_ref << "The" << ' ' << 3 << ' ' << "Musketeers? " << true;
        EXPECT_EQ(vari, "The 3 Musketeers? true");
        EXPECT_EQ(vari_ref, "The 3 Musketeers? true");
    }
    {   // stream to fstr with float and boolean
        fstr::fstr31 vari;
        vari << "The" << ' ' << 3.1415 << ' ' << "Musketeers? " << false;
        EXPECT_EQ(vari, "The 3.141500000000000181 Musketeers? false");
    }
    {   // stream to fstr_ref with float and boolean
        fstr::fstr31 vari;
        fstr::fstr_ref vari_ref{vari};
        vari_ref << "The" << ' ' << 3.1415 << ' ' << "Musketeers? " << false;
        EXPECT_EQ(vari, "The 3.1415 Musketeers? false");
        EXPECT_EQ(vari_ref, "The 3.1415 Musketeers? false");
    }
}
