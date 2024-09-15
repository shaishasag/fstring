#include "gtest/gtest.h"
#include "fstring.h"

// empty string should identify as empty no matter how it was made empty

TEST(EmptyTests, Empty)
{
    {
        fstr::fstr31 no_init;
        fstr::fstr31 empty_init{""};
        fstr::fstr31 cleared_init{"dodo"}; cleared_init.clear();
        fstr::fstr31 assigned_init = no_init;

        EXPECT_TRUE(no_init.empty());
        EXPECT_TRUE(empty_init.empty());
        EXPECT_TRUE(cleared_init.empty());
        EXPECT_TRUE(assigned_init.empty());

        EXPECT_TRUE(no_init == "");
        EXPECT_TRUE(empty_init == "");
        EXPECT_TRUE(cleared_init == "");
        EXPECT_TRUE(assigned_init == "");

        EXPECT_TRUE(no_init == empty_init);
        EXPECT_TRUE(empty_init == cleared_init);
        EXPECT_TRUE(cleared_init == no_init);
        EXPECT_TRUE(assigned_init == cleared_init);

        std::string str;
        EXPECT_TRUE(no_init == str);
        EXPECT_TRUE(empty_init == str);
        EXPECT_TRUE(cleared_init == str);
        EXPECT_TRUE(assigned_init == str);

        std::string_view str_view;
        EXPECT_TRUE(no_init == str_view);
        EXPECT_TRUE(empty_init == str_view);
        EXPECT_TRUE(cleared_init == str_view);
        EXPECT_TRUE(assigned_init == str_view);
    }
}
