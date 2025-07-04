#include "gtest/gtest.h"
#include "fstring.h"

/// Verify constructing constexpr fstr::fstr_base
/// This is more of a compilation test than a runtime test
TEST(Constexpr, expr_simple)
{
    {
        constexpr fstr::fstr31 empty;
        EXPECT_EQ(empty.capacity(), 31);
        EXPECT_STREQ(empty.c_str(), "");
        EXPECT_TRUE(empty.empty());
        EXPECT_FALSE(empty.full());
        EXPECT_EQ(empty.size(), 0);

        fstr::fstr_ref empty_ref{empty};
        EXPECT_EQ(empty_ref.capacity(), 31);
        EXPECT_STREQ(empty_ref.c_str(), "");
        EXPECT_TRUE(empty_ref.empty());
        EXPECT_FALSE(empty_ref.full());
        EXPECT_EQ(empty_ref.size(), 0);
    }
    {
        constexpr fstr::fstr31 con("Kajagoogoo");
        EXPECT_EQ(con.capacity(), 31);
        EXPECT_STREQ(con.c_str(), "Kajagoogoo");
        EXPECT_FALSE(con.empty());
        EXPECT_FALSE(con.full());
        EXPECT_EQ(con.size(), 10);

        fstr::fstr_ref con_ref = con;
        EXPECT_EQ(con_ref.capacity(), 31);
        EXPECT_STREQ(con_ref.c_str(), "Kajagoogoo");
        EXPECT_FALSE(con_ref.empty());
        EXPECT_FALSE(con_ref.full());
        EXPECT_EQ(con_ref.size(), 10);
    }
}

/// Verify initializing constexpr fstr::fstr_base, const fstr::fstr_ref with constexpr fstr::fstr_base
TEST(Constexpr, expr_compound)
{
    constexpr fstr::fstr31 con1("Kajagoogoo");
    {
        constexpr fstr::fstr31 con2(con1);
        EXPECT_EQ(con2.capacity(), 31);
        EXPECT_STREQ(con2.c_str(), "Kajagoogoo");
        EXPECT_FALSE(con2.empty());
        EXPECT_FALSE(con2.full());
        EXPECT_EQ(con2.size(), 10);
    }
    {
        const fstr::fstr_ref ref1(con1);
        EXPECT_EQ(ref1.capacity(), 31);
        EXPECT_STREQ(ref1.c_str(), "Kajagoogoo");
        EXPECT_FALSE(ref1.empty());
        EXPECT_FALSE(ref1.full());
        EXPECT_EQ(ref1.size(), 10);
    }
}

void func1(const fstr::fstr31 in_str)
{
    EXPECT_EQ(in_str.capacity(), 31);
}
void func2(const fstr::fstr31& in_str)
{
    EXPECT_EQ(in_str.capacity(), 31);
}
void func3(const fstr::fstr_ref in_str_ref)
{
    EXPECT_EQ(in_str_ref.capacity(), 31);
}

/// Passing constexpr fstr::fstr_base to function, by value, by reference and as fstr::fstr_ref
TEST(Constexpr, pass_to_func)
{
    constexpr fstr::fstr31 con1("Kajagoogoo");
    {
        constexpr fstr::fstr31 con2(con1);
        func1(con1);
        func1(con2);
        func2(con1);
        func2(con2);
        func3(con1);
        func3(con2);
    }
}

/// Call functions marked as constexpr on constexpr fstr::fstr_base
TEST(Constexpr, call_constexpr)
{
    constexpr fstr::fstr31 con1("Kajagoogoo");
    constexpr bool b = con1.sv().ends_with("googoo");
    EXPECT_TRUE(b);

    constexpr fstr::size_type pos = con1.sv().find_last_of('g');
    EXPECT_EQ(pos, 7);
}
