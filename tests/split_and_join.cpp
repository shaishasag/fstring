#include "gtest/gtest.h"
#include <unordered_map>
#include "fstring.h"
#include "fstringstream.h"

TEST(SplitAndJoin, join)
{
    {
        // join empty list should produce empty string
        std::vector<fstr::fstr31> split_ends;
        auto delimiter = "++"sv;
        
        fstr::fstr31 joined_str;
        fstr::join(split_ends.begin(), split_ends.end(), delimiter, joined_str);
        
        EXPECT_EQ(joined_str, ""sv);
    }
    {
        // join single value list should produce the same value
        std::vector<fstr::fstr31> split_ends{"Hila"};
        auto delimiter = "++"sv;
        
        fstr::fstr31 joined_str;
        fstr::join(split_ends.begin(), split_ends.end(), delimiter, joined_str);
        
        EXPECT_EQ(joined_str, "Hila"sv);
    }
    {
        std::vector<fstr::fstr31> split_ends{"Hila", "Lulu", "Lin"};
        auto delimiter = "++"sv;
        
        fstr::fstr31 joined_str;
        fstr::join(split_ends.begin(), split_ends.end(), delimiter, joined_str);
        
        EXPECT_EQ(joined_str, "Hila++Lulu++Lin"sv);
    }
}

TEST(SplitAndJoin, split)
{
    std::string_view  delimiter = "++"sv;
    
    {   // split empty string
        std::string_view to_split = ""sv;
        std::vector<fstr::fstr31> splits;

        fstr::split(to_split, delimiter, splits);

        std::vector<fstr::fstr31> expected_splits{};

        EXPECT_EQ(splits, expected_splits);
    }
    {   // split string with just the delimiter
        std::vector<fstr::fstr31> splits;

        fstr::split(delimiter, delimiter, splits);

        std::vector<fstr::fstr31> expected_splits{};

        EXPECT_EQ(splits, expected_splits);
    }
    {
        // split string with no delimiter
        std::string_view to_split = "Hila"sv;
        std::vector<fstr::fstr31> splits;

        fstr::split(to_split, delimiter, splits);

        std::vector<fstr::fstr31> expected_splits{"Hila"};

        EXPECT_EQ(splits, expected_splits);
    }
    {
        // split string with delimiter at the end
        std::string_view to_split = "Hila++"sv;
        std::vector<fstr::fstr31> splits;

        fstr::split(to_split, delimiter, splits);

        std::vector<fstr::fstr31> expected_splits{"Hila"};

        EXPECT_EQ(splits, expected_splits);
    }
    {
        // split string with delimiter at the beginning
        std::string_view to_split = "++Hila"sv;
        std::vector<fstr::fstr31> splits;
        
        fstr::split(to_split, delimiter, splits);

        std::vector<fstr::fstr31> expected_splits{"Hila"};

        EXPECT_EQ(splits, expected_splits);
    }
    {
        // full split
        std::string_view to_split = "Hila++Lulu++Lin"sv;
        std::vector<fstr::fstr31> splits;

        fstr::split(to_split, delimiter, splits);

        std::vector<fstr::fstr31> expected_splits{"Hila", "Lulu", "Lin"};

        EXPECT_EQ(splits, expected_splits);
    }
}
