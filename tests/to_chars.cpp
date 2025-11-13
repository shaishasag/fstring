#include "gtest/gtest.h"
#include "fstring.h"

using namespace fstr;

TEST(ToChars, simple)
{
    {   // integer
        fstr31 fs;
        fs.to_chars(0);
        EXPECT_EQ(fs.sv(), "0"sv);
    }
    {   // floating point: zero
        fstr31 fs;
        fs.to_chars(0.0);
        EXPECT_EQ(fs.sv(), "0"sv);
    }
    {   // floating point
        fstr31 fs;
        fs.to_chars(0.1);
        EXPECT_EQ(fs.sv(), "0.1"sv);
    }
    {   // to_chars append
        fstr31 fs;
        fs.to_chars(1);
        EXPECT_EQ(fs.sv(), "1"sv);
        fs.to_chars(2); // append 2
        EXPECT_EQ(fs.sv(), "12"sv);
    }
    {   // to_chars after cleat
        fstr31 fs;
        fs.to_chars(1.1);
        EXPECT_EQ(fs.sv(), "1.1"sv);
        fs.clear();
        fs.to_chars(2.2);
        EXPECT_EQ(fs.sv(), "2.2"sv);
    }
    {
        fstr31 fs;
        fs.to_chars(float(78.90f));
        EXPECT_EQ(fs.sv(), "78.9"sv);
        fs.clear();
        fs.to_chars(double(78.90));
        EXPECT_EQ(fs.sv(), "78.9"sv);
        fs.clear();
        fs.to_chars((long double)(78.90));
        EXPECT_EQ(fs.sv(), "78.9"sv);
    }
    {
        fstr31 fs;
        fs.to_chars(float(123.456f));
        EXPECT_EQ(fs.sv(), "123.456"sv);
        fs.clear();
        fs.to_chars(double(123.456));
        EXPECT_EQ(fs.sv(), "123.456"sv);
        fs.clear();
        fs.to_chars((long double)(123.456));
        EXPECT_EQ(fs.sv(), "123.456"sv);
    }
    {
        fstr31 fs;
        fs.to_chars(float(0.001234f));
        EXPECT_EQ(fs.sv(), "0.001234"sv);
        fs.clear();
        fs.to_chars(double(0.001234));
        EXPECT_EQ(fs.sv(), "0.001234"sv);
        fs.clear();
        fs.to_chars((long double)(0.001234));
        EXPECT_EQ(fs.sv(), "0.001234"sv);
    }
    {
        fstr31 fs;
        fs.to_chars(100.0123456789f);
        EXPECT_EQ(fs.sv(), "100.012344"sv);
        fs.clear();
        fs.to_chars(double(9876543210.0123456789));
        EXPECT_EQ(fs.sv(), "9876543210.012346"sv);
        fs.clear();
        fs.to_chars((long double)(9876543210.0123456789));
        EXPECT_EQ(fs.sv(), "9876543210.012346"sv);
    }
//    {   // Hex format
//        fstr31 fs;
//        fs.to_chars(int64_t{9876543210}, "0x%llX"sv);
//        EXPECT_EQ(fs.sv(), "0x24CB016EA"sv);
//    }
}

TEST(ToChars, exact_size_buffer)
{
    {   // integer
        fstr15 fs("abcdefghijklmn"sv);
        size_t num_chars = fs.to_chars(1);
        EXPECT_EQ(num_chars, 1);
        EXPECT_EQ(fs.sv(), "abcdefghijklmn1"sv);
    }
    {   // float
        fstr15 fs("abcdefghijklmn"sv);
        size_t num_chars = fs.to_chars(1.0);
        EXPECT_EQ(num_chars, 1);
        EXPECT_EQ(fs.sv(), "abcdefghijklmn1"sv);
    }
}

TEST(ToChars, full_buffer)
{
    {   // integer
        fstr15 fs("abcdefghijklmno"sv);
        size_t num_chars = fs.to_chars(0);
        EXPECT_EQ(num_chars, 0);
        EXPECT_EQ(fs.sv(), "abcdefghijklmno"sv);
    }
}

TEST(ToChars, too_small_buffer)
{
    {
        fstr15 fs("abcdefghijklmnopqrstuvwxyz"sv);
        fs.resize(12);
        size_t num_chars = fs.to_chars(1.0101);
        EXPECT_EQ(num_chars, 0);
        // value too large, string should not change
        EXPECT_EQ(fs.sv(), "abcdefghijkl"sv);
    }
    {   // same but with reference
        fstr15 fs("abcdefghijklmnopqrstuvwxyz"sv);
        fs.resize(12);
        fstr::fstr_ref fs_ref(fs);
        size_t num_chars = fs_ref.to_chars(1.0101);
        EXPECT_EQ(num_chars, 0);
        // value too large, string should not change
        EXPECT_EQ(fs_ref.sv(), "abcdefghijkl"sv);
    }
}

TEST(Format, basic_format)
{
    {
        fstr63 fs("A message: ");
        size_t num_chars = fs.format("Hello {}, you have {} new messages",
                                     "Shai", 3);
        EXPECT_EQ(num_chars, 35);
        EXPECT_EQ(fs.size(), 46);
        // value too large, string should not change
        EXPECT_EQ(fs.sv(), "A message: Hello Shai, you have 3 new messages"sv);
    }
    {   // same but with reference
        fstr63 fs("A message: ");
        fstr::fstr_ref fs_ref(fs);
        size_t num_chars = fs_ref.format("Hello {}, you have {} new messages",
                                     "Shai", 3);
        EXPECT_EQ(num_chars, 35);
        EXPECT_EQ(fs_ref.size(), 46);
        // value too large, string should not change
        EXPECT_EQ(fs_ref.sv(), "A message: Hello Shai, you have 3 new messages"sv);
    }
}

TEST(Format, fstr_too_short)
{
    {
        fstr31 fs("A message: ");
        size_t num_chars = fs.format("Hello {}, you have {} new messages",
                                     "Shai", 3);
        EXPECT_EQ(num_chars, 20);
        EXPECT_EQ(fs.size(), 31);
        // value too large, string should not change
        EXPECT_EQ(fs.sv(), "A message: Hello Shai, you have"sv);
    }
    {   // same but with reference
        fstr31 fs("A message: ");
        fstr::fstr_ref fs_ref(fs);
        size_t num_chars = fs_ref.format("Hello {}, you have {} new messages",
                                     "Shai", 3);
        EXPECT_EQ(num_chars, 20);
        EXPECT_EQ(fs_ref.size(), 31);
        // value too large, string should not change
        EXPECT_EQ(fs_ref.sv(), "A message: Hello Shai, you have"sv);
    }
}

TEST(Format, compare)
{
    double f{1.123456789};
    
    {
        fstr31 fs_printf; fs_printf.printf(f);
        std::cout << "fs_printf: " << fs_printf.sv() << std::endl;
    }

    {
        fstr31 fs_to_chars; fs_to_chars.to_chars(f);
        std::cout << "fs_to_chars: " << fs_to_chars.sv() << std::endl;
    }

    {
        fstr31 fs_format; fs_format.format("{}", f);
        std::cout << "fs_format: " << fs_format.sv() << std::endl;
    }

}
