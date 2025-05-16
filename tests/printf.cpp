#include "gtest/gtest.h"
#include "fstring.h"

using namespace fstr;

TEST(Printf, simple)
{
    {
        fstr31 fs;
        fs.printf(0);
        EXPECT_STREQ(fs.c_str(), "0");
    }
    {
        fstr31 fs;
        fs.printf(0.0);
        EXPECT_STREQ(fs.c_str(), "0.0");
    }
    {
        fstr31 fs;
        fs.printf(1);
        EXPECT_STREQ(fs.c_str(), "1");
        fs.printf(2); // append 2
        EXPECT_STREQ(fs.c_str(), "12");
    }
    {
        fstr31 fs;
        fs.printf(1.0);
        EXPECT_STREQ(fs.c_str(), "1.0");
        fs.clear();
        fs.printf(2.0);
        EXPECT_STREQ(fs.c_str(), "2.0");
    }
    {
        fstr31 fs;
        fs.printf(float(78.90f));
        EXPECT_STREQ(fs.c_str(), "78.9000015259");
        fs.clear();
        fs.printf(double(78.90));
        EXPECT_STREQ(fs.c_str(), "78.900000000000005684");
        fs.clear();
        fs.printf((long double)(78.90));
        EXPECT_STREQ(fs.c_str(), "78.900000000000005684");
    }
    {
        fstr31 fs;
        fs.printf(float(123.456f));
        EXPECT_STREQ(fs.c_str(), "123.456001");
        fs.clear();
        fs.printf(double(123.456));
        EXPECT_STREQ(fs.c_str(), "123.456");
        fs.clear();
        fs.printf((long double)(123.456));
        EXPECT_STREQ(fs.c_str(), "123.456");
    }
    {
        fstr31 fs;
        fs.printf(float(0.001234f));
        EXPECT_STREQ(fs.c_str(), "0.001234");
        fs.clear();
        fs.printf(double(0.001234));
        EXPECT_STREQ(fs.c_str(), "0.001234");
        fs.clear();
        fs.printf((long double)(0.001234));
        EXPECT_STREQ(fs.c_str(), "0.001234");
    }
    {
        fstr31 fs;
        fs.printf(100.0123456789f);
        EXPECT_STREQ(fs.c_str(), "100.012344");
        fs.clear();
        fs.printf(double(9876543210.0123456789));
        EXPECT_STREQ(fs.c_str(), "9876543210.012346");
        fs.clear();
        fs.printf((long double)(9876543210.0123456789));
        EXPECT_STREQ(fs.c_str(), "9876543210.012346");
    }
    {   // Hex format
        fstr31 fs;
        fs.printf(int64_t{9876543210}, "0x%llX");
        EXPECT_STREQ(fs.c_str(), "0x24CB016EA");
    }
}
