#include "gtest/gtest.h"
#include "fstring.h"

using namespace fixed;

template<typename ToScanf>
void scanf_by_type(fixed::fstring_ref in_text, const ToScanf expected, const char* in_format=nullptr)
{
    // the varaible to read are the first item in and array
    // the second item if there to check that scanf does not overflow because of wrong format
    ToScanf thing[2]{std::numeric_limits<ToScanf>::max()/2, std::numeric_limits<ToScanf>::max()};
    ASSERT_NE(expected, std::numeric_limits<ToScanf>::max()/2);

    in_text.scanf(thing[0], in_format);
    EXPECT_EQ(thing[0], expected);
    EXPECT_EQ(thing[1], std::numeric_limits<ToScanf>::max());
}

TEST(Scanf, simple)
{
    {
        fstring31 fs("0");
        scanf_by_type<short>(fs, 0);
        scanf_by_type<unsigned short>(fs, 0);
        scanf_by_type<long>(fs, 0);
        scanf_by_type<unsigned long>(fs, 0);
        scanf_by_type<long long>(fs, 0);
        scanf_by_type<unsigned long long>(fs, 0);
    }
    {
        fstring31 fs("1717");
        scanf_by_type<short>(fs, 1717);
        scanf_by_type<unsigned short>(fs, 1717);
        scanf_by_type<long>(fs, 1717);
        scanf_by_type<unsigned long>(fs, 1717);
        scanf_by_type<long long>(fs, 1717);
        scanf_by_type<unsigned long long>(fs, 1717);
    }
    {
        fstring31 fs("-1717");
        scanf_by_type<short>(fs, -1717);
        scanf_by_type<long>(fs, -1717);
        scanf_by_type<long long>(fs, -1717);
    }
    {
        fstring31 fs("0.0");
        scanf_by_type<float>(fs, 0.0f);
        scanf_by_type<double>(fs, 0.0);
        scanf_by_type<long double>(fs, 0.0);
    }
    {
        fstring31 fs("1.0");
        scanf_by_type<float>(fs, 1.0f);
        scanf_by_type<double>(fs, 1.0);
        scanf_by_type<long double>(fs, 1.0);
    }
    {
        fstring31 fs("-1.0");
        scanf_by_type<float>(fs, -1.0f);
        scanf_by_type<double>(fs, -1.0);
        scanf_by_type<long double>(fs, -1.0);
    }
}
