#include "gtest/gtest.h"
#include "fstring.h"

TEST(Find, find_plain_text)
{
    {   // find plain text in fstring
        constexpr fixed::fstring31 con("Kajagoogoo");
        auto pos = con.find('g');
        EXPECT_EQ(pos, 4);

        pos = con.find('z');
        EXPECT_EQ(pos, fixed::npos);

        pos = con.find("goo");
        EXPECT_EQ(pos, 4);

        pos = con.find("zoo");
        EXPECT_EQ(pos, fixed::npos);

        pos = con.find(std::string_view("goo"));
        EXPECT_EQ(pos, 4);

        pos = con.find(std::string_view("zoo"));
        EXPECT_EQ(pos, fixed::npos);
    }

    {   // find plain text in fstring_ref
        constexpr fixed::fstring31 con("Kajagoogoo");
        fixed::fstring_ref con_ref(con);

        auto pos = con_ref.find('g');
        EXPECT_EQ(pos, 4);

        pos = con_ref.find('z');
        EXPECT_EQ(pos, fixed::npos);

        pos = con_ref.find("goo");
        EXPECT_EQ(pos, 4);

        pos = con_ref.find("zoo");
        EXPECT_EQ(pos, fixed::npos);

        pos = con_ref.find(std::string_view("goo"));
        EXPECT_EQ(pos, 4);

        pos = con_ref.find(std::string_view("zoo"));
        EXPECT_EQ(pos, fixed::npos);
   }
}


TEST(Find, find_fstring)
{
    {   // find fstring in fstring
        constexpr fixed::fstring31 con("Kajagoogoo");
        
        auto pos = con.find(fixed::fstring7('g'));
        EXPECT_EQ(pos, 4);

        pos = con.find(fixed::fstring7('z'));
        EXPECT_EQ(pos, fixed::npos);

        pos = con.find(fixed::fstring7("goo"));
        EXPECT_EQ(pos, 4);

        pos = con.find(fixed::fstring7("zoo"));
        EXPECT_EQ(pos, fixed::npos);
    }

    {   // find fstring in fstring_ref
        constexpr fixed::fstring31 con("Kajagoogoo");
        fixed::fstring_ref con_ref(con);

        auto pos = con_ref.find(fixed::fstring7('g'));
        EXPECT_EQ(pos, 4);

        pos = con_ref.find(fixed::fstring7('z'));
        EXPECT_EQ(pos, fixed::npos);

        pos = con_ref.find(fixed::fstring7("goo"));
        EXPECT_EQ(pos, 4);

        pos = con_ref.find(fixed::fstring7("zoo"));
        EXPECT_EQ(pos, fixed::npos);
   }
}



TEST(Find, find_fstring_ref)
{
    constexpr fixed::fstring31 con("Kajagoogoo");
    {   // find fstring_ref in fstring
        {
            fixed::fstring7 g('g');
            fixed::fstring_ref g_ref(g);
            auto pos = con.find(g_ref);
            EXPECT_EQ(pos, 4);
        }
        {
            fixed::fstring7 z('z');
            fixed::fstring_ref z_ref(z);
            auto pos = con.find(z_ref);
            EXPECT_EQ(pos, fixed::npos);
        }
        {
            fixed::fstring7 goo("goo");
            fixed::fstring_ref goo_ref(goo);
            auto pos = con.find(goo_ref);
            EXPECT_EQ(pos, 4);
        }
        {
            fixed::fstring7 zoo("zoo");
            fixed::fstring_ref zoo_ref(zoo);
            auto pos = con.find(zoo_ref);
            EXPECT_EQ(pos, fixed::npos);
        }
    }

    {   // find fstring_ref in fstring_ref
        fixed::fstring_ref con_ref(con);
        {
            fixed::fstring7 g('g');
            fixed::fstring_ref g_ref(g);
            auto pos = con_ref.find(g_ref);
            EXPECT_EQ(pos, 4);
        }
        {
            fixed::fstring7 z('z');
            fixed::fstring_ref z_ref(z);
            auto pos = con_ref.find(z_ref);
            EXPECT_EQ(pos, fixed::npos);
        }
        {
            fixed::fstring7 goo("goo");
            fixed::fstring_ref goo_ref(goo);
            auto pos = con_ref.find(goo_ref);
            EXPECT_EQ(pos, 4);
        }
        {
            fixed::fstring7 zoo("zoo");
            fixed::fstring_ref zoo_ref(zoo);
            auto pos = con_ref.find(zoo_ref);
            EXPECT_EQ(pos, fixed::npos);
        }
    }
}
