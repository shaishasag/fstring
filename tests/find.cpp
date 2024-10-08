#include "gtest/gtest.h"
#include "fstring.h"

TEST(Find, find_plain_text)
{
    {   // find plain text in fstring
        constexpr fstr::fstr31 con("Kajagoogoo");
        auto pos = con.sv().find('g');
        EXPECT_EQ(pos, 4);

        pos = con.sv().find('z');
        EXPECT_EQ(pos, fstr::npos);

        pos = con.sv().find("goo");
        EXPECT_EQ(pos, 4);

        pos = con.sv().find("zoo");
        EXPECT_EQ(pos, fstr::npos);

        pos = con.sv().find(std::string_view("goo"));
        EXPECT_EQ(pos, 4);

        pos = con.sv().find(std::string_view("zoo"));
        EXPECT_EQ(pos, fstr::npos);
    }

    {   // find plain text in fstr_ref
        constexpr fstr::fstr31 con("Kajagoogoo");
        fstr::fstr_ref con_ref(con);

        auto pos = con_ref.sv().find('g');
        EXPECT_EQ(pos, 4);

        pos = con_ref.sv().find('z');
        EXPECT_EQ(pos, fstr::npos);

        pos = con_ref.sv().find("goo");
        EXPECT_EQ(pos, 4);

        pos = con_ref.sv().find("zoo");
        EXPECT_EQ(pos, fstr::npos);

        pos = con_ref.sv().find(std::string_view("goo"));
        EXPECT_EQ(pos, 4);

        pos = con_ref.sv().find(std::string_view("zoo"));
        EXPECT_EQ(pos, fstr::npos);
   }
}


TEST(Find, find_fstring)
{
    {   // find fstring in fstring
        constexpr fstr::fstr31 con("Kajagoogoo");
        
        auto pos = con.sv().find(fstr::fstr7('g'));
        EXPECT_EQ(pos, 4);

        pos = con.sv().find(fstr::fstr7('z'));
        EXPECT_EQ(pos, fstr::npos);

        pos = con.sv().find(fstr::fstr7("goo"));
        EXPECT_EQ(pos, 4);

        pos = con.sv().find(fstr::fstr7("zoo"));
        EXPECT_EQ(pos, fstr::npos);
    }

    {   // find fstring in fstr_ref
        constexpr fstr::fstr31 con("Kajagoogoo");
        fstr::fstr_ref con_ref(con);

        auto pos = con_ref.sv().find(fstr::fstr7('g'));
        EXPECT_EQ(pos, 4);

        pos = con_ref.sv().find(fstr::fstr7('z'));
        EXPECT_EQ(pos, fstr::npos);

        pos = con_ref.sv().find(fstr::fstr7("goo"));
        EXPECT_EQ(pos, 4);

        pos = con_ref.sv().find(fstr::fstr7("zoo"));
        EXPECT_EQ(pos, fstr::npos);
   }
}



TEST(Find, find_fstr_ref)
{
    constexpr fstr::fstr31 con("Kajagoogoo");
    {   // find fstr_ref in fstring
        {
            fstr::fstr7 g('g');
            fstr::fstr_ref g_ref(g);
            auto pos = con.sv().find(g_ref);
            EXPECT_EQ(pos, 4);
        }
        {
            fstr::fstr7 z('z');
            fstr::fstr_ref z_ref(z);
            auto pos = con.sv().find(z_ref);
            EXPECT_EQ(pos, fstr::npos);
        }
        {
            fstr::fstr7 goo("goo");
            fstr::fstr_ref goo_ref(goo);
            auto pos = con.sv().find(goo_ref);
            EXPECT_EQ(pos, 4);
        }
        {
            fstr::fstr7 zoo("zoo");
            fstr::fstr_ref zoo_ref(zoo);
            auto pos = con.sv().find(zoo_ref);
            EXPECT_EQ(pos, fstr::npos);
        }
    }

    {   // find fstr_ref in fstr_ref
        fstr::fstr_ref con_ref(con);
        {
            fstr::fstr7 g('g');
            fstr::fstr_ref g_ref(g);
            auto pos = con_ref.sv().find(g_ref);
            EXPECT_EQ(pos, 4);
        }
        {
            fstr::fstr7 z('z');
            fstr::fstr_ref z_ref(z);
            auto pos = con_ref.sv().find(z_ref);
            EXPECT_EQ(pos, fstr::npos);
        }
        {
            fstr::fstr7 goo("goo");
            fstr::fstr_ref goo_ref(goo);
            auto pos = con_ref.sv().find(goo_ref);
            EXPECT_EQ(pos, 4);
        }
        {
            fstr::fstr7 zoo("zoo");
            fstr::fstr_ref zoo_ref(zoo);
            auto pos = con_ref.sv().find(zoo_ref);
            EXPECT_EQ(pos, fstr::npos);
        }
    }
}
