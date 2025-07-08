#include "gtest/gtest.h"
#include "fstring.h"

TEST(Replace, replace_zero_chars)
{
    std::string_view origi{"SuperCaliFragilisticExpialiDocious"};

    {   // place zero chars with none
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 0, "");
        super_fixed.replace(5, 0, "");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
    {   // place zero chars with one
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 0, "X");
        super_fixed.replace(5, 0, "X");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // place zero chars with many
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 0, "KALLISTRY");
        super_fixed.replace(5, 0, "KALLISTRY");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
}

TEST(Replace, replace_one_char)
{
    std::string_view origi{"SuperCaliFragilisticExpialiDocious"};
    {   // place one char with none
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 1, "");
        super_fixed.replace(5, 1, "");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
    {   // place one char with one
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 1, "X");
        super_fixed.replace(5, 1, "X");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // place one char with many
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 1, "KALLISTRY");
        super_fixed.replace(5, 1, "KALLISTRY");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
}

TEST(Replace, replace_few_chars)
{
    std::string_view origi{"SuperCaliFragilisticExpialiDocious"};

    {   // place few chars with none
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 4, "");
        super_fixed.replace(5, 4, "");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
    {   // place few chars with one
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 4, "X");
        super_fixed.replace(5, 4, "X");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // place few chars with many
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 4, "KALLISTRY");
        super_fixed.replace(5, 4, "KALLISTRY");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
}

TEST(Replace, some_examples)
{
    std::string_view origi{"0123456789"};
    EXPECT_STREQ(std::string(origi).replace(2, 5, "").c_str(), "01789");
    EXPECT_STREQ(std::string(origi).replace(2, 5, "abc").c_str(), "01abc789");
    EXPECT_STREQ(std::string(origi).replace(2, 5, "abcdefg").c_str(), "01abcdefg789");
    EXPECT_STREQ(std::string(origi).replace(2, 8, "").c_str(), "01");
    EXPECT_STREQ(std::string(origi).replace(2, 8, "abc").c_str(), "01abc");
    EXPECT_STREQ(std::string(origi).replace(2, 8, "abcdefg").c_str(), "01abcdefg");
    EXPECT_STREQ(std::string(origi).replace(2, 19, "").c_str(), "01");
    EXPECT_STREQ(std::string(origi).replace(2, 19, "abc").c_str(), "01abc");
    EXPECT_STREQ(std::string(origi).replace(2, 19, "abcdefg").c_str(), "01abcdefg");

    EXPECT_STREQ(fstr::fstr63(origi).replace(2, 5, "").c_str(), "01789");
    EXPECT_STREQ(fstr::fstr63(origi).replace(2, 5, "abc").c_str(), "01abc789");
    EXPECT_STREQ(fstr::fstr63(origi).replace(2, 5, "abcdefg").c_str(), "01abcdefg789");
    EXPECT_STREQ(fstr::fstr63(origi).replace(2, 8, "").c_str(), "01");
    EXPECT_STREQ(fstr::fstr63(origi).replace(2, 8, "abc").c_str(), "01abc");
    EXPECT_STREQ(fstr::fstr63(origi).replace(2, 8, "abcdefg").c_str(), "01abcdefg");
    EXPECT_STREQ(fstr::fstr63(origi).replace(2, 19, "").c_str(), "01");
    EXPECT_STREQ(fstr::fstr63(origi).replace(2, 19, "abc").c_str(), "01abc");
    EXPECT_STREQ(fstr::fstr63(origi).replace(2, 19, "abcdefg").c_str(), "01abcdefg");

    using f10 = fstr::fstring_base<10, char>;
    EXPECT_STREQ(f10(origi).replace(2, 5, "").c_str(), "01789");
    EXPECT_STREQ(f10(origi).replace(2, 5, "abc").c_str(), "01abc789");
    EXPECT_STREQ(f10(origi).replace(2, 5, "abcdefg").c_str(), "01abcdefg7");
    EXPECT_STREQ(f10(origi).replace(2, 8, "").c_str(), "01");
    EXPECT_STREQ(f10(origi).replace(2, 8, "abc").c_str(), "01abc");
    EXPECT_STREQ(f10(origi).replace(2, 8, "abcdefg").c_str(), "01abcdefg");
    EXPECT_STREQ(f10(origi).replace(2, 19, "").c_str(), "01");
    EXPECT_STREQ(f10(origi).replace(2, 19, "abc").c_str(), "01abc");
    EXPECT_STREQ(f10(origi).replace(2, 19, "abcdefg").c_str(), "01abcdefg");

    using f8 = fstr::fstring_base<8, char>;
    EXPECT_STREQ(f8(origi).replace(2, 5, "").c_str(), "017");
    EXPECT_STREQ(f8(origi).replace(2, 5, "abc").c_str(), "01abc7");
    EXPECT_STREQ(f8(origi).replace(2, 5, "abcdefg").c_str(), "01abcdef");
    EXPECT_STREQ(f8(origi).replace(2, 8, "").c_str(), "01");
    EXPECT_STREQ(f8(origi).replace(2, 8, "abc").c_str(), "01abc");
    EXPECT_STREQ(f8(origi).replace(2, 8, "abcdefg").c_str(), "01abcdef");
    EXPECT_STREQ(f8(origi).replace(2, 19, "").c_str(), "01");
    EXPECT_STREQ(f8(origi).replace(2, 19, "abc").c_str(), "01abc");
    EXPECT_STREQ(f8(origi).replace(2, 19, "abcdefg").c_str(), "01abcdef");
}

TEST(Replace, replace_many_chars)
{
    std::string_view origi{"SuperCaliFragilisticExpialiDocious"};

    {   // replace many chars with none
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 20, "");
        super_fixed.replace(5, 20, "");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
    {   // replace many chars with one
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 20, "X");
        super_fixed.replace(5, 20, "X");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // replace many chars with few
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 20, "KALLISTRY");
        super_fixed.replace(5, 20, "KALLISTRY");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // replace too many chars with few
        std::string super_std(origi);
        fstr::fstr63 super_fixed(origi);
        super_std.replace(5, 200, "KALLISTRY");
        super_fixed.replace(5, 200, "KALLISTRY");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
}


TEST(Replace, replace_and_throw)
{
    std::string_view origi{"SuperCaliFragilisticExpialiDocious"};
    {
        fstr::fstr63 super_fixed(origi);
        EXPECT_THROW({ // should throw is pos too large
            super_fixed.replace(super_fixed.size(), 5, "KALLISTRY");
        }, std::out_of_range );
        EXPECT_STREQ(super_fixed.c_str(), origi.data());  // string should not change after throwing
    }

    {
        std::string_view very_long_replacement("KALLISTRY/KALLISTRY/KALLISTRY/KALLISTRY/KALLISTRY/KALLISTRY");
        fstr::fstr63 super_fixed(origi);
        std::string ss(origi);
        ss.replace(6, 7, very_long_replacement);
        ss.resize(super_fixed.capacity());
        super_fixed.replace(6, 7, very_long_replacement);
        EXPECT_STREQ(super_fixed.c_str(), ss.c_str());
    }
}


TEST(Replace, replace_all)
{
    {   // replace nothing with nothing - string should not change
        fstr::fstr63 f1("AABBAABBAA");
        f1.replace_all("", "");
        EXPECT_EQ(f1, "AABBAABBAA"sv);
    }
    {   // replace nothing with something - string should not change
        fstr::fstr63 f1("AABBAABBAA");
        f1.replace_all("", "CC");
        EXPECT_EQ(f1, "AABBAABBAA"sv);
    }
    {   // replace something with nothing
        fstr::fstr63 f1("AABBAABBAA");
        f1.replace_all("AA", "");
        EXPECT_EQ(f1, "BBBB"sv);
    }
    {   // replace something with something smaller
        fstr::fstr63 f1("AABBAABBAA");
        f1.replace_all("AA", "C");
        EXPECT_EQ(f1, "CBBCBBC"sv);
    }
    {   // replace something with something same size
        fstr::fstr63 f1("AABBAABBAA");
        f1.replace_all("AA", "CC");
        EXPECT_EQ(f1, "CCBBCCBBCC"sv);
    }
    {   // replace something with something bigger
        fstr::fstr63 f1("AABBAABBAA");
        f1.replace_all("AA", "CCC");
        EXPECT_EQ(f1, "CCCBBCCCBBCCC"sv);
    }
    {   // replace something with the same string
        fstr::fstr63 f1("AABBAABBAA");
        f1.replace_all("AB", "AB");
        EXPECT_EQ(f1, "AABBAABBAA"sv);
    }
    {   // replacement too long to fit
        fstr::fstr15 f1("AABBAABBAABBAA");
        f1.replace_all("AAB", "1000");
        EXPECT_EQ(f1, "1000B1000B1000B"sv);
    }
}
TEST(Replace, replace_all_ref)
{
    {   // replace nothing with nothing - string should not change
        fstr::fstr63 f1("AABBAABBAA");
        fstr::fstr_ref f1_ref(f1);
        f1_ref.replace_all("", "");
        EXPECT_EQ(f1_ref, "AABBAABBAA"sv);
    }
    {   // replace nothing with something - string should not change
        fstr::fstr63 f1("AABBAABBAA");
        fstr::fstr_ref f1_ref(f1);
        f1_ref.replace_all("", "CC");
        EXPECT_EQ(f1_ref, "AABBAABBAA"sv);
    }
    {   // replace something with nothing
        fstr::fstr63 f1("AABBAABBAA");
        fstr::fstr_ref f1_ref(f1);
        f1_ref.replace_all("AA", "");
        EXPECT_EQ(f1_ref, "BBBB"sv);
    }
    {   // replace something with something smaller
        fstr::fstr63 f1("AABBAABBAA");
        fstr::fstr_ref f1_ref(f1);
        f1_ref.replace_all("AA", "C");
        EXPECT_EQ(f1_ref, "CBBCBBC"sv);
    }
    {   // replace something with something same size
        fstr::fstr63 f1("AABBAABBAA");
        fstr::fstr_ref f1_ref(f1);
        f1_ref.replace_all("AA", "CC");
        EXPECT_EQ(f1_ref, "CCBBCCBBCC"sv);
    }
    {   // replace something with something bigger
        fstr::fstr63 f1("AABBAABBAA");
        fstr::fstr_ref f1_ref(f1);
        f1_ref.replace_all("AA", "CCC");
        EXPECT_EQ(f1_ref, "CCCBBCCCBBCCC"sv);
    }
    {   // replace something with the same string
        fstr::fstr63 f1("AABBAABBAA");
        fstr::fstr_ref f1_ref(f1);
        f1_ref.replace_all("AB", "AB");
        EXPECT_EQ(f1_ref, "AABBAABBAA"sv);
    }
    {   // replacement too long to fit
        fstr::fstr15 f1("AABBAABBAABBAA");
        fstr::fstr_ref f1_ref(f1);
        f1_ref.replace_all("AAB", "1000");
        EXPECT_EQ(f1_ref, "1000B1000B1000B"sv);
    }
}
