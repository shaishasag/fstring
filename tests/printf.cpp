#include "gtest/gtest.h"
#include "fstring.h"

using namespace fixed;

TEST(Printf, simple)
{
    {
        fstring31 fs;
        fs.printf(0);
        EXPECT_STREQ(fs.c_str(), "0");
    }
    {
        fstring31 fs;
        fs.printf(0.0);
        EXPECT_STREQ(fs.c_str(), "0.0");
    }
    {
        fstring31 fs;
        fs.printf(1);
        EXPECT_STREQ(fs.c_str(), "1");
        fs.printf(2); // append 2
        EXPECT_STREQ(fs.c_str(), "12");
    }
    {
        fstring31 fs;
        fs.printf(1.0);
        EXPECT_STREQ(fs.c_str(), "1.0");
        fs.printf(2.0);
        EXPECT_STREQ(fs.c_str(), "1.02.0");
    }
    {
        fstring31 fs;
        fs.printf(float(78.90f));
        EXPECT_STREQ(fs.c_str(), "78.900002");
        fs.clear();
        fs.printf(double(78.90));
        EXPECT_STREQ(fs.c_str(), "78.9");
    }
    {
        fstring31 fs;
        fs.printf(float(123.456f));
        EXPECT_STREQ(fs.c_str(), "123.456001");
        fs.clear();
        fs.printf(double(123.456));
        EXPECT_STREQ(fs.c_str(), "123.456");
    }
    {
        fstring31 fs;
        fs.printf(float(0.001234f));
        EXPECT_STREQ(fs.c_str(), "0.001234");
        fs.clear();
        fs.printf(double(0.001234));
        EXPECT_STREQ(fs.c_str(), "0.001234");
    }
    {
        fstring31 fs;
        fs.printf(100.0123456789f);
        EXPECT_STREQ(fs.c_str(), "100.012344");
        fs.clear();
        fs.printf(double(9876543210.0123456789));
        EXPECT_STREQ(fs.c_str(), "9876543210.012346");
    }
    {   // Hex format
        fstring31 fs;
        fs.printf(int64_t{9876543210}, "0x%llX");
        EXPECT_STREQ(fs.c_str(), "0x24CB016EA");
    }
}
