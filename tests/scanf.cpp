#include "gtest/gtest.h"
#include "fstring.h"
#include "fstringstream.h"

using namespace fstr;

template<typename ToScanf>
void scanf_by_type(fstr::fstr_ref in_text, const ToScanf expected, const char* in_format=nullptr)
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
        fstr31 fs("0");
        scanf_by_type<short>(fs, 0);
        scanf_by_type<unsigned short>(fs, 0);
        scanf_by_type<long>(fs, 0);
        scanf_by_type<unsigned long>(fs, 0);
        scanf_by_type<long long>(fs, 0);
        scanf_by_type<unsigned long long>(fs, 0);
    }
    {
        fstr31 fs("1717");
        scanf_by_type<short>(fs, 1717);
        scanf_by_type<unsigned short>(fs, 1717);
        scanf_by_type<long>(fs, 1717);
        scanf_by_type<unsigned long>(fs, 1717);
        scanf_by_type<long long>(fs, 1717);
        scanf_by_type<unsigned long long>(fs, 1717);
    }
    {
        fstr31 fs("-1717");
        scanf_by_type<short>(fs, -1717);
        scanf_by_type<long>(fs, -1717);
        scanf_by_type<long long>(fs, -1717);
    }
    {
        fstr31 fs("0.0");
        scanf_by_type<float>(fs, 0.0f);
        scanf_by_type<double>(fs, 0.0);
        scanf_by_type<long double>(fs, 0.0);
    }
    {
        fstr31 fs("1.0");
        scanf_by_type<float>(fs, 1.0f);
        scanf_by_type<double>(fs, 1.0);
        scanf_by_type<long double>(fs, 1.0);
    }
    {
        fstr31 fs("-1.0");
        scanf_by_type<float>(fs, -1.0f);
        scanf_by_type<double>(fs, -1.0);
        scanf_by_type<long double>(fs, -1.0);
    }
}


template<typename ToTest>
void round_trip_test(const ToTest value)
{
    {
        const ToTest d{value};
        fstr31 fs;
        fs.printf(d);
        ToTest dd{static_cast<ToTest>(value/2 + 1)};
        fs.scanf(dd);
        EXPECT_EQ(d, dd);
    }

    {
        const ToTest d{value};
        fstr31 fs;
        fs << d;
        ToTest dd{static_cast<ToTest>(value/2 + 1)};
        fs >> dd;
        EXPECT_EQ(d, dd);
    }
}

template<typename ToTest>
void round_trip_test_many_values(ToTest jump=1)
{
    size_t num_tests{0};

    ToTest stop_at{static_cast<ToTest>(std::numeric_limits<ToTest>::max()-jump-1)};
    for (ToTest i = std::numeric_limits<ToTest>::min(); i < stop_at; i += jump)
    {
        round_trip_test<ToTest>(i);
        ++num_tests;
        //std::cout << num_tests << ") " << i << std::endl;
    }
    std::cout << "tested " << num_tests << " values of "<< typeid(ToTest).name() << std::endl;
}

#if 0
TEST(Scanf, round_trip)
{
    round_trip_test_many_values<short>();
    round_trip_test_many_values<unsigned short>();
    round_trip_test_many_values<long>(9222537906415);
    round_trip_test_many_values<unsigned long>(9222537906415);
    round_trip_test_many_values<long long>(9222537906415);
    round_trip_test_many_values<unsigned long long>(9222537906415);

    round_trip_test<float>(-1.0f);
    round_trip_test<double>(-1.0);
    round_trip_test<long double>(-1.0);
}
#endif
