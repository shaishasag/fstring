#include "gtest/gtest.h"
#include "fstring.h"


TEST(BeginEnd, ForwardLoop)
{
    {
        fstr::fstr7 fs_in;
        size_t iterations_count = 0;
        for (auto i = fs_in.begin(); i != fs_in.end(); ++i)
        {
            ++iterations_count;
        }
        EXPECT_EQ(iterations_count, fs_in.size()); // looping empty string should have 0 iteration
    }
    {
        fstr::fstr7 fs_in{'a'};
        size_t iterations_count = 0;
        for (auto i = fs_in.begin(); i != fs_in.end(); ++i)
        {
            ++iterations_count;
        }
        EXPECT_EQ(iterations_count, fs_in.size()); // looping 1 char string should have 1 iteration
    }
    {
        fstr::fstr7 fs_in{"1234567"};
        size_t iterations_count = 0;
        for (auto i = fs_in.begin(); i != fs_in.end(); ++i)
        {
            ++iterations_count;
        }
        EXPECT_EQ(iterations_count, fs_in.size()); // looping full string should have 1 iteration
    }
}

TEST(BeginEnd, BackwardLoop)
{
    {
        fstr::fstr31 fs_in;
        size_t iterations_count = 0;
        for (auto i = fs_in.rbegin(); i != fs_in.rend(); ++i)
        {
            ++iterations_count;
        }
        EXPECT_EQ(iterations_count, 0); // looping empty string should have 0 iteration
    }
    {
        fstr::fstr7 fs_in{'a'};
        size_t iterations_count = 0;
        for (auto i = fs_in.rbegin(); i != fs_in.rend(); ++i)
        {
            ++iterations_count;
        }
        EXPECT_EQ(iterations_count, fs_in.size()); // looping 1 char string should have 1 iteration
    }
    {
        fstr::fstr7 fs_in{"1234567"};
        auto ib = *fs_in.rbegin();
        auto ie = *fs_in.rend();
        size_t iterations_count = 0;
        for (auto i = fs_in.rbegin(); i != fs_in.rend(); ++i)
        {
            ++iterations_count;
        }
        EXPECT_EQ(iterations_count, fs_in.size()); // looping full string should have 1 iteration
    }
}

TEST(BeginEnd, ForwardLoopAndCopy)
{
    {
        fstr::fstr31 fs_in("abc");
        fstr::fstr31 fs_out("xyz");

        // loop using begin()/end() and copying each char to fs_out
        // result should be that fs_in and fs_out are equal
        int32_t out_index = 0;
        for (auto i = fs_in.begin(); i != fs_in.end(); ++i)
        {
            fs_out[out_index] = *i;
            ++out_index;
        }
        EXPECT_EQ(out_index, fs_out.size());
        EXPECT_EQ(fs_in, fs_out);
    }
    {
        fstr::fstr31 fs_in;
        fstr::fstr31 fs_out("xyz");

        // loop using begin()/end() and copying each char to fs_out
        // since fs_in is empty, fs_out should not change
        int32_t out_index = 0;
        for (auto i = fs_in.begin(); i != fs_in.end(); ++i)
        {
            fs_out[out_index] = *i;
            ++out_index;
        }
        EXPECT_EQ(out_index, 0);
        EXPECT_EQ(fs_out, "xyz");
    }
}

TEST(BeginEnd, BackwardLoopAndCopy)
{
    {
        fstr::fstr31 fs_in("abc");
        fstr::fstr31 fs_out("xyz");

        // loop using rbegin()/rend() and copying each char to fs_out
        // result should be that fs_in and fs_out are equal
        int32_t out_index = static_cast<int32_t>(fs_out.size() - 1);
        for (auto i = fs_in.rbegin(); i != fs_in.rend(); ++i)
        {
            fs_out[out_index] = *i;
            --out_index;
        }
        EXPECT_EQ(out_index, -1);
        EXPECT_EQ(fs_in, fs_out);
    }
    {
        fstr::fstr31 fs_in;
        fstr::fstr31 fs_out("xyz");

        // loop using rbegin()/rend() and copying each char to fs_out
        // since fs_in is empty, fs_out should not change
        int32_t out_index = static_cast<int32_t>(fs_out.size() - 1);
        for (auto i = fs_in.rbegin(); i != fs_in.rend(); ++i)
        {
            fs_out[out_index] = *i;
            --out_index;
        }
        EXPECT_EQ(out_index,static_cast<int32_t>(fs_out.size() - 1));
        EXPECT_EQ(fs_out, "xyz");
    }
}
