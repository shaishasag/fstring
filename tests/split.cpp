#include <string_view>
#include <vector>
#include "gtest/gtest.h"
#include "fstringstream.h"

using sv_vec = std::vector<std::string_view>;

TEST(SplitTest, BasicSingleCharDelimiter)
{
    sv_vec result = fstr::split("a,b,c", ",");
    sv_vec expected_result = sv_vec({"a", "b", "c"});

    sv_vec result_skip_empty = fstr::split("a,b,c", ",", true);
    sv_vec expected_result_skip_empty = sv_vec({"a", "b", "c"});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, LeadingDelimiter)
{
    sv_vec result = fstr::split(",a,b", ",");
    sv_vec expected_result = sv_vec({"", "a", "b"});

    sv_vec result_skip_empty = fstr::split(",a,b", ",", true);
    sv_vec expected_result_skip_empty = sv_vec({"a", "b"});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, TrailingDelimiter)
{
    sv_vec result = fstr::split("a,b,", ",");
    sv_vec expected_result = sv_vec({"a", "b", ""});

    sv_vec result_skip_empty = fstr::split("a,b,", ",", true);
    sv_vec expected_result_skip_empty = sv_vec({"a", "b"});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, ConsecutiveDelimiters)
{
    sv_vec result = fstr::split("a,,b", ",");
    sv_vec expected_result = sv_vec({"a", "", "b"});

    sv_vec result_skip_empty = fstr::split("a,,b", ",", true);
    sv_vec expected_result_skip_empty = sv_vec({"a", "b"});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, OnlyDelimiter)
{
    sv_vec result = fstr::split(",", ",");
    sv_vec expected_result = sv_vec({"", ""});

    sv_vec result_skip_empty = fstr::split(",", ",", true);
    sv_vec expected_result_skip_empty = sv_vec({});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, EmptyInputString)
{
    sv_vec result = fstr::split("", ",");
    sv_vec expected_result = sv_vec({""});

    sv_vec result_skip_empty = fstr::split("", ",", true);
    sv_vec expected_result_skip_empty = sv_vec({});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, NoDelimiterFound)
{
    sv_vec result = fstr::split("abc", ",");
    sv_vec expected_result = sv_vec({"abc"});

    sv_vec result_skip_empty = fstr::split("abc", ",", true);
    sv_vec expected_result_skip_empty = sv_vec({"abc"});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, MultiCharDelimiter)
{
    sv_vec result = fstr::split("a::b::c", "::");
    sv_vec expected_result = sv_vec({"a", "b", "c"});

    sv_vec result_skip_empty = fstr::split("a::b::c", "::", true);
    sv_vec expected_result_skip_empty = sv_vec({"a", "b", "c"});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, MultiCharLeadingDelimiter)
{
    sv_vec result = fstr::split("::a::b", "::");
    sv_vec expected_result = sv_vec({"", "a", "b"});

    sv_vec result_skip_empty = fstr::split("::a::b", "::", true);
    sv_vec expected_result_skip_empty = sv_vec({"a", "b"});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, MultiCharTrailingDelimiter)
{
    sv_vec result = fstr::split("a::b::", "::");
    sv_vec expected_result = sv_vec({"a", "b", ""});

    sv_vec result_skip_empty = fstr::split("a::b::", "::", true);
    sv_vec expected_result_skip_empty = sv_vec({"a", "b"});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, MultiCharConsecutiveDelimiters)
{
    sv_vec result = fstr::split("a::::b", "::");
    sv_vec expected_result = sv_vec({"a", "", "b"});

    sv_vec result_skip_empty = fstr::split("a::::b", "::", true);
    sv_vec expected_result_skip_empty = sv_vec({"a", "b"});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, MultiCharOnlyDelimiter)
{
    sv_vec result = fstr::split("::", "::");
    sv_vec expected_result = sv_vec({"", ""});

    sv_vec result_skip_empty = fstr::split("::", "::", true);
    sv_vec expected_result_skip_empty = sv_vec({});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}

TEST(SplitTest, EmptyDelimiterThrows)
{
    EXPECT_THROW(fstr::split("a,b,c", ""), std::invalid_argument);
    EXPECT_THROW(fstr::split("a,b,c", "", true), std::invalid_argument);
}

TEST(SplitTest, OnlyDelimitersNoContent)
{
    sv_vec result = fstr::split(",,,", ",");
    sv_vec expected_result = sv_vec({"", "", "", ""});

    sv_vec result_skip_empty = fstr::split(",,,", ",", true);
    sv_vec expected_result_skip_empty = sv_vec({});

    EXPECT_EQ(result, expected_result);
    EXPECT_EQ(result_skip_empty, expected_result_skip_empty);
}
