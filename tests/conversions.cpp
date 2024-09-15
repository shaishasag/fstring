#include "gtest/gtest.h"
#include "fstring/fstring.h"
#include "fstring/fstringstream.h"

using namespace fstr;

size_t get_size_sv(std::string_view in_sv)
{
    return in_sv.size();
}

TEST(Conversions, string_view)
{
    std::string_view banana_sv{"bananarama"};
    EXPECT_EQ(get_size_sv(banana_sv), banana_sv.size());
    
    fstr15 banana_fixed{banana_sv};  // fstring intialized from string_view
    EXPECT_EQ(get_size_sv(banana_fixed), banana_fixed.size());
    
    [[maybe_unused]] std::string_view fruit_sv_1{banana_fixed};  // string_view initialized from fstring
    [[maybe_unused]] std::string_view fruit_sv_2(banana_fixed);  // string_view initialized from fstring
    [[maybe_unused]] std::string_view fruit_sv_3 = banana_fixed;  // string_view initialized from fstring
}

TEST(Conversions, minimal)
{
    fstr7 f7;
    fstr7 ref7{f7};
    fstr7 f15;
    fstr7 ref15{f15};
    const char* cstr = "cstr";
    std::string_view sv{cstr};
    std::string str{sv};

    if (f7 == cstr) {
        f7 << cstr;
    }
    if (ref7 == cstr) {
        ref7 << cstr;
    }

    if (f7 == sv) {
        f7 << sv;
    }
    if (ref7 == sv) {
        ref7 << sv;
    }

    if (f7 == str) {
        f7 << str;
    }
    if (ref7 == str) {
        ref7 << str;
    }

    // f7, ref7, f15, ref15
    if (f7 == ref7) {
        f7 << ref7;
    }
    if (f7 == f15) {
        f7 << f15;
    }
    if (f7 == ref15) {
        f7 << ref15;
    }

    if (ref7 == f7) {
        ref7 << f7;
    }
    if (ref7 == f15) {
        ref7 << f15;
    }
    if (ref7 == ref15) {
        ref7 << ref15;
    }

    if (f15 == f7) {
        ref7 << f7;
    }
    if (f15 == ref7) {
        ref7 << f15;
    }
    if (f15 == ref15) {
        ref7 << ref15;
    }

    if (ref15 == f7) {
        ref7 << f7;
    }
    if (ref15 == ref7) {
        ref7 << f15;
    }
    if (ref15 == f15) {
        ref7 << ref15;
    }
}
