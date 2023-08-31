#include "gtest/gtest.h"
#include "fstring.h"

using namespace fixed;


TEST(AccessTests, operator_square_brackets_at)
{
    {
        std::string std_str("my bologna");
        fixed::fstring15 ms1(std_str);
        for (size_t i = 0; i < std_str.size(); ++i){
            EXPECT_EQ(ms1[i], std_str[i]);
        }
        for (size_t i = 0; i < std_str.size(); ++i){
            EXPECT_EQ(ms1.at(i), std_str.at(i));
        }

        EXPECT_EQ(ms1.front(), std_str.front());
        EXPECT_EQ(ms1.back(), std_str.back());
    }
}

TEST(AccessTests, operator_at_exception)
{
    {   // at(pos) on empty string should throw for any pos
        fixed::fstring15 ms_empty;
        for (size_t i = 0; i < 17; ++i) {
            EXPECT_THROW(ms_empty.at(i), std::out_of_range);
        }
    }
    {   // at(pos) on string should throw if pos >= size()
        fixed::fstring15 ms1("my bologna");
        for (size_t i = 0; i < ms1.size(); ++i){
            EXPECT_NO_THROW(ms1.at(i));
        }
        for (size_t i = ms1.size(); i < ms1.size()*2; ++i){
            EXPECT_THROW(ms1.at(i), std::out_of_range);
        }

        // at(pos) on cleared string should throw for any pos
        ms1.clear();
        for (size_t i = 0; i < 17; ++i) {
            EXPECT_THROW(ms1.at(i), std::out_of_range);
        }
    }
}

TEST(AccessTests, iterators)
{
    {
        std::string std_str("my bologna");
        fixed::fstring15 ms1(std_str);
        EXPECT_NE(ms1.begin(), ms1.end());
        EXPECT_EQ(std::distance(ms1.begin(), ms1.end()), (ptrdiff_t)ms1.size());

        for (auto i = ms1.begin(); i != ms1.end(); ++i) {
            EXPECT_EQ(*i, std_str[std::distance(ms1.begin(), i)]);
        }
        size_t si = 0;
        for (auto i : ms1) {
            EXPECT_EQ(i, std_str[si++]);
        }
    }
    {   // for empty string ms1.begin() == ms1.end()
        fixed::fstring15 ms1("");
        EXPECT_EQ(ms1.begin(), ms1.end());
        EXPECT_EQ(std::distance(ms1.begin(), ms1.end()), (ptrdiff_t)ms1.size());

        bool in_loop = false;
        for (auto i = ms1.begin(); i != ms1.end(); ++i){
            in_loop = true;
        }
        EXPECT_FALSE(in_loop);

        in_loop = false;
        for ([[maybe_unused]] auto i : ms1){
            in_loop = true;
        }
        EXPECT_FALSE(in_loop);
    }
}


TEST(AccessTests, const_iterators)
{
    {
        std::string std_str("my bologna");
        const fixed::fstring15 ms1(std_str);
        EXPECT_NE(ms1.cbegin(), ms1.cend());
        EXPECT_EQ(std::distance(ms1.cbegin(), ms1.cend()), (ptrdiff_t)ms1.size());

        for (auto i = ms1.cbegin(); i != ms1.cend(); ++i) {
            EXPECT_EQ(*i, std_str[std::distance(ms1.cbegin(), i)]);
        }
    }
    {   // for empty string ms1.begin() == ms1.end()
        fixed::fstring15 ms1("");
        EXPECT_EQ(ms1.cbegin(), ms1.cend());
        EXPECT_EQ(std::distance(ms1.cbegin(), ms1.cend()), (ptrdiff_t)ms1.size());

        bool in_loop = false;
        for (auto i = ms1.cbegin(); i != ms1.cend(); ++i){
            in_loop = true;
        }
        EXPECT_FALSE(in_loop);
    }
}
