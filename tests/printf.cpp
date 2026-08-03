#include "gtest/gtest.h"
#include "fstring.h"

using namespace fstr;

TEST(Printf, simple)
{
    {
        fstr31 fs;
        fs.printf(0);
        EXPECT_EQ(fs.sv(), "0"sv);
    }
    {
        fstr31 fs;
        fs.printf(0.0);
        EXPECT_EQ(fs.sv(), "0.0"sv);
    }
    {
        fstr31 fs;
        fs.printf(1);
        EXPECT_EQ(fs.sv(), "1"sv);
        fs.printf(2); // append 2
        EXPECT_EQ(fs.sv(), "12"sv);
    }
    {
        fstr31 fs;
        fs.printf(1.0);
        EXPECT_EQ(fs.sv(), "1.0"sv);
        fs.clear();
        fs.printf(2.0);
        EXPECT_EQ(fs.sv(), "2.0"sv);
    }
    {
        fstr31 fs;
        fs.printf(float(78.90f));
        EXPECT_EQ(fs.sv(), "78.900001526"sv);
        fs.clear();
        fs.printf(double(78.90));
        EXPECT_EQ(fs.sv(), "78.90000000000000568"sv);
        fs.clear();
        fs.printf((long double)(78.90));
        EXPECT_EQ(fs.sv(), "78.90000000000000568"sv);
    }
    {
        fstr31 fs;
        fs.printf(float(123.456f));
        EXPECT_EQ(fs.sv(), "123.456001282"sv);
        fs.clear();
        fs.printf(double(123.456));
        EXPECT_EQ(fs.sv(), "123.45600000000000307"sv);
        fs.clear();
        fs.printf((long double)(123.456));
        EXPECT_EQ(fs.c_str(), "123.45600000000000307"sv);
    }
    {
        fstr31 fs;
        fs.printf(float(0.001234f));
        EXPECT_EQ(fs.sv(), "0.001234"sv);
        fs.clear();
        fs.printf(double(0.001234));
        EXPECT_EQ(fs.sv(), "0.001234"sv);
        fs.clear();
        fs.printf((long double)(0.001234));
        EXPECT_EQ(fs.sv(), "0.001234"sv);
    }
    {
        fstr31 fs;
        fs.printf(100.0123456789f);
        EXPECT_EQ(fs.sv(), "100.01234436"sv);
        fs.clear();
        fs.printf(double(9876543210.0123456789));
        EXPECT_EQ(fs.sv(), "9876543210.01234626770019531"sv);
        fs.clear();
        fs.printf((long double)(9876543210.0123456789));
        EXPECT_EQ(fs.sv(), "9876543210.01234626770019531"sv);
    }
    {   // Hex format
        fstr31 fs;
        fs.printf(int64_t{9876543210}, "0x%llX");
        EXPECT_EQ(fs.sv(), "0x24CB016EA"sv);
    }
}
