#include <string_view>
#include <vector>
#include "gtest/gtest.h"
#include "fstringstream.h"

using sv_vec = std::vector<std::string_view>;

static void test_join_expected(const sv_vec& parts,
                               std::string_view delim,
                               std::string_view expected,
                               std::string_view description)
{
    // std::string version
    std::string std_result = "prefix:";
    fstr::join(parts, delim, std_result);
    EXPECT_EQ(std_result, std::string("prefix:") + std::string(expected))
       << "[std::string] Test failed: " << description;

    // fstr_ref version
    fstr::fstr31 fstr_result("prefix:");
    // fstr_result might be too short, expected behaviour is to append as much as possible
    std::string_view expected_result_with_fstr(std_result.data(),
                                          std::min(std_result.size(), fstr_result.max_size()));
    fstr::join(parts, delim, fstr_result);

    EXPECT_EQ(fstr_result.sv(), expected_result_with_fstr)
       << "[fstr_ref] Test failed: " << description;
}


TEST(JoinTest, EmptyVector)
{
    test_join_expected({}, ",", "", "Empty input vector");
}

TEST(JoinTest, SingleElement)
{
    test_join_expected({"only"}, ",", "only", "Single element, non-empty");
}

TEST(JoinTest, BasicJoin)
{
    test_join_expected({"a", "b", "c"}, ",", "a,b,c", "Basic 3-element join with comma");
}

TEST(JoinTest, EmptyDelimiter)
{
    test_join_expected({"a", "b", "c"}, "", "abc", "Join with empty delimiter");
}

TEST(JoinTest, MultiCharDelimiter)
{
    test_join_expected({"a", "b", "c"}, "::", "a::b::c", "Multi-character delimiter");
}

TEST(JoinTest, EmptyStringsInParts)
{
    test_join_expected({"", "x", "", "y"}, "-", "-x--y", "Mix of empty and non-empty strings");
}

TEST(JoinTest, AllEmptyStrings)
{
    test_join_expected({"", "", ""}, ",", ",,", "All elements empty with non-empty delimiter");
}

TEST(JoinTest, AllEmptyNoDelimiter)
{
    test_join_expected({"", "", ""}, "", "", "All elements empty with no delimiter");
}

TEST(JoinTest, LeadingEmptyWithDelimiter)
{
    test_join_expected({"", "b", "c"}, ",", ",b,c", "Leading empty part");
}

TEST(JoinTest, TrailingEmptyWithDelimiter)
{
    test_join_expected({"a", "b", ""}, ",", "a,b,", "Trailing empty part");
}

TEST(JoinTest, NoDelimiterBetweenEmpty)
{
    test_join_expected({"", "", ""}, "", "", "All parts empty, empty delimiter");
}

TEST(JoinTest, DelimiterWithSpaces)
{
    test_join_expected({"x", "y", "z"}, " ", "x y z", "Delimiter is a single space");
}


TEST(JoinTest, ResultTooLongForFStr)
{
    test_join_expected({"x0123456789", "y0123456789", "z0123456789"}, "++", "x0123456789++y0123456789++z0123456789", "result too long for fstr");
}

