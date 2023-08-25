#include "gtest/gtest.h"
#include "fstring.h"

using namespace fixed;

TEST(Conversions, minimal)
{
    fstring7 f7;
    fstring7 ref7{f7};
    fstring7 f15;
    fstring7 ref15{f15};
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
