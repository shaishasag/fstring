#include "gtest/gtest.h"
#include "fstring.h"

TEST(Replace, replace_zero_chars)
{
    std::string_view origi{"SuperCaliFragilisticExpialiDocious"};

    {   // place zero chars with none
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 0, "");
        super_fixed.replace(5, 0, "");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
    {   // place zero chars with one
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 0, "X");
        super_fixed.replace(5, 0, "X");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // place zero chars with many
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
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
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 1, "");
        super_fixed.replace(5, 1, "");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
    {   // place one char with one
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 1, "X");
        super_fixed.replace(5, 1, "X");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // place one char with many
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
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
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 4, "");
        super_fixed.replace(5, 4, "");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
    {   // place few chars with one
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 4, "X");
        super_fixed.replace(5, 4, "X");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // place few chars with many
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 4, "KALLISTRY");
        super_fixed.replace(5, 4, "KALLISTRY");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
}

TEST(Replace, replace_many_chars)
{
    std::string_view origi{"SuperCaliFragilisticExpialiDocious"};

    {   // place many chars with none
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 20, "");
        super_fixed.replace(5, 20, "");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
    {   // place many chars with one
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 20, "X");
        super_fixed.replace(5, 20, "X");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // place many chars with few
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 20, "KALLISTRY");
        super_fixed.replace(5, 20, "KALLISTRY");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }

    {   // place too many chars with few
        std::string super_std(origi);
        fixed::fstring63 super_fixed(origi);
        super_std.replace(5, 200, "KALLISTRY");
        super_fixed.replace(5, 200, "KALLISTRY");
        EXPECT_STREQ(super_fixed.c_str(), super_std.c_str());
    }
}


TEST(Replace, replace_and_throw)
{
    std::string_view origi{"SuperCaliFragilisticExpialiDocious"};
    {
        fixed::fstring63 super_fixed(origi);
        EXPECT_THROW({ // should throw is pos too large
            super_fixed.replace(super_fixed.size(), 5, "KALLISTRY");
        }, std::out_of_range );
        EXPECT_STREQ(super_fixed.c_str(), origi.data());  // string should not change after throwing
    }

    {
        fixed::fstring63 super_fixed(origi);
        EXPECT_THROW({
            super_fixed.replace(6, 7, "KALLISTRY/KALLISTRY/KALLISTRY/KALLISTRY/KALLISTRY/KALLISTRY");
        }, std::length_error );
        EXPECT_STREQ(super_fixed.c_str(), origi.data());  // string should not change after throwing
    }

}
