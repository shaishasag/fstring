#include "gtest/gtest.h"
#include "fstring.h"

TEST(InsertTests, InsertChar)
{
    fixed::fstring15 fx;
    fx.insert(0, 2, '3').insert(2, 1, '6');  // chain inserts
    EXPECT_STREQ(fx.c_str(), "336");
    EXPECT_EQ(fx.size(), 3);

    fx.insert(1, 1, '+');
    EXPECT_STREQ(fx.c_str(), "3+36");
    EXPECT_EQ(fx.size(), 4);
    
    fx.insert(3, 1, '=');
    EXPECT_STREQ(fx.c_str(), "3+3=6");
    EXPECT_EQ(fx.size(), 5);

    EXPECT_THROW({
        fx.insert(5, 23, '.');  // insert above capacity
    }, std::length_error );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3+3=6");
    EXPECT_EQ(fx.size(), 5);

    EXPECT_THROW({
        fx.insert(6, 1, '.');  // insert above size
    }, std::out_of_range );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3+3=6");
    EXPECT_EQ(fx.size(), 5);

}

TEST(InsertTests, InsertCharPtr)
{
    fixed::fstring15 fx;
    fx.insert(0, "32").insert(2, "6");  // chain inserts
    EXPECT_STREQ(fx.c_str(), "326");
    EXPECT_EQ(fx.size(), 3);

    fx.insert(1, "**");
    EXPECT_STREQ(fx.c_str(), "3**26");
    EXPECT_EQ(fx.size(), 5);

    fx.insert(4, "=3+");
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

    EXPECT_THROW({
        fx.insert(3, "--------");  // insert above capacity
    }, std::length_error );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

    EXPECT_THROW({
        fx.insert(10, "-");  // insert above size
    }, std::out_of_range );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

}


TEST(InsertTests, InsertCharPtrCount)
{
    fixed::fstring15 fx;
    fx.insert(0, "32xxxxxxxxxxxx", 2).insert(2, "6xxxxxxxxxxxx", 1);  // chain inserts
    EXPECT_STREQ(fx.c_str(), "326");
    EXPECT_EQ(fx.size(), 3);

    fx.insert(1, "**xxxxxxxxxxxx", 2);
    EXPECT_STREQ(fx.c_str(), "3**26");
    EXPECT_EQ(fx.size(), 5);

    fx.insert(4, "=3+xxxxxxxxxxxx", 3);
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);
}

TEST(InsertTests, InsertStringView)
{
    fixed::fstring15 fx;
    fx.insert(0, std::string_view("32")).insert(2, std::string_view("6"));  // chain inserts
    EXPECT_STREQ(fx.c_str(), "326");
    EXPECT_EQ(fx.size(), 3);

    fx.insert(1, std::string_view("**"));
    EXPECT_STREQ(fx.c_str(), "3**26");
    EXPECT_EQ(fx.size(), 5);

    fx.insert(4, std::string_view("=3+"));
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

    EXPECT_THROW({
        fx.insert(3, std::string_view("--------"));  // insert above capacity
    }, std::length_error );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

    EXPECT_THROW({
        fx.insert(10, std::string_view("-"));  // insert above size
    }, std::out_of_range );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

}

TEST(InsertTests, InsertStringViewCount)
{
    fixed::fstring15 fx;
    fx.insert(0, std::string_view("32xxxxxxxxxxxx"), 2).insert(2, std::string_view("6xxxxxxxxxxxx"), 1);  // chain inserts
    EXPECT_STREQ(fx.c_str(), "326");
    EXPECT_EQ(fx.size(), 3);

    fx.insert(1, std::string_view("**xxxxxxxxxxxx"), 2);
    EXPECT_STREQ(fx.c_str(), "3**26");
    EXPECT_EQ(fx.size(), 5);

    fx.insert(4, std::string_view("=3+xxxxxxxxxxxx"), 3);
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);
}

TEST(InsertTests, InsertFString)
{
    fixed::fstring15 fx;
    fx.insert(0, fixed::fstring15("32")).insert(2, fixed::fstring15("6"));  // chain inserts
    EXPECT_STREQ(fx.c_str(), "326");
    EXPECT_EQ(fx.size(), 3);

    fx.insert(1, fixed::fstring15("**"));
    EXPECT_STREQ(fx.c_str(), "3**26");
    EXPECT_EQ(fx.size(), 5);

    fx.insert(4, fixed::fstring15("=3+"));
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

    EXPECT_THROW({
        fx.insert(3, fixed::fstring15("--------"));  // insert above capacity
    }, std::length_error );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

    EXPECT_THROW({
        fx.insert(10, fixed::fstring15("-"));  // insert above size
    }, std::out_of_range );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

}

TEST(InsertTests, InsertFStringCount)
{
    fixed::fstring15 fx;
    fx.insert(0, fixed::fstring15("32xxxxxxxxxxxx"), 2).insert(2, fixed::fstring15("6xxxxxxxxxxxx"), 1);  // chain inserts
    EXPECT_STREQ(fx.c_str(), "326");
    EXPECT_EQ(fx.size(), 3);

    fx.insert(1, fixed::fstring15("**xxxxxxxxxxxx"), 2);
    EXPECT_STREQ(fx.c_str(), "3**26");
    EXPECT_EQ(fx.size(), 5);

    fx.insert(4, fixed::fstring15("=3+xxxxxxxxxxxx"), 3);
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);
}

TEST(InsertTests, InsertFStringRef)
{
    fixed::fstring15 f1("32");
    fixed::fstring_ref f1_ref(f1);
    fixed::fstring15 f2("6");
    fixed::fstring_ref f2_ref(f2);

    fixed::fstring15 fx;
    fx.insert(0, f1_ref).insert(2, f2_ref);  // chain inserts
    EXPECT_STREQ(fx.c_str(), "326");
    EXPECT_EQ(fx.size(), 3);

    fixed::fstring15 f3("**");
    fixed::fstring_ref f3_ref(f3);
    fx.insert(1, f3_ref);
    EXPECT_STREQ(fx.c_str(), "3**26");
    EXPECT_EQ(fx.size(), 5);

    fixed::fstring15 f4("=3+");
    fixed::fstring_ref f4_ref(f4);
    fx.insert(4, f4_ref);
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

    EXPECT_THROW({
        fixed::fstring15 f5("--------");
        fixed::fstring_ref f5_ref(f5);
        fx.insert(3, f5_ref);  // insert above capacity
    }, std::length_error );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

    EXPECT_THROW({
        fixed::fstring15 f6("-");
        fixed::fstring_ref f6_ref(f6);
        fx.insert(10, f6_ref);  // insert above size
    }, std::out_of_range );
    // string should not change
    EXPECT_STREQ(fx.c_str(), "3**2=3+6");
    EXPECT_EQ(fx.size(), 8);

}

TEST(InsertTests, PushBack)
{
    {   // push to empty string
        fixed::fstring15 s;
        s.push_back('?');
        EXPECT_STREQ(s.c_str(),"?");
        s.push_back('!');
        EXPECT_STREQ(s.c_str(),"?!");
    }
    {   // push to non empty string
        fixed::fstring15 s("Cahoots");
        s.push_back('?');
        EXPECT_STREQ(s.c_str(),"Cahoots?");
        s.push_back('!');
        EXPECT_STREQ(s.c_str(),"Cahoots?!");
    }

    {
        fixed::fstring15 furs("Psychedelic Fur");
        EXPECT_THROW({
            // push_back to a full string
            furs.push_back('s'); 
        }, std::length_error );
        EXPECT_STREQ(furs.c_str(), "Psychedelic Fur");  // string should not change after throwing
    }
}
