#include "gtest/gtest.h"
#include "fstring.h"

// Verify fstr::fstring::starts_with, fstr::fstring::ends_with, , fstr::fstring::contains
TEST(CompareTests, starts_ends_contains)
{

    {
        fstr::fstr31 original("The Psychedelic Furs");

        fstr::fstr31 reference(original);
        EXPECT_TRUE(original == reference);
        EXPECT_TRUE(original.starts_with('T'));
        EXPECT_TRUE(original.starts_with("The"));
        EXPECT_TRUE(original.ends_with("Furs"));
        EXPECT_TRUE(original.ends_with('s'));
        EXPECT_FALSE(original.starts_with("the"));
        EXPECT_FALSE(original.ends_with("furs"));
        EXPECT_TRUE(original.contains(""));
        EXPECT_TRUE(original.contains('d'));
        EXPECT_FALSE(original.contains('Z'));
        EXPECT_TRUE(original.contains("delic"));
        EXPECT_FALSE(original.contains("dElic"));
        EXPECT_TRUE(original.contains("The Psychedelic Furs"));
        
        EXPECT_TRUE(reference.starts_with('T'));
        EXPECT_TRUE(reference.starts_with("The"));
        EXPECT_TRUE(reference.ends_with("Furs"));
        EXPECT_TRUE(reference.ends_with('s'));
        EXPECT_FALSE(reference.starts_with("the"));
        EXPECT_FALSE(reference.ends_with("furs"));
        EXPECT_TRUE(reference.contains(""));
        EXPECT_TRUE(reference.contains('d'));
        EXPECT_FALSE(reference.contains('Z'));
        EXPECT_TRUE(reference.contains("delic"));
        EXPECT_FALSE(reference.contains("dElic"));
        EXPECT_TRUE(reference.contains("The Psychedelic Furs"));
    }
}

/// Verify fstr::fstring::operator==, fstr::fstring::compare
/// when used with const char*, std::string, std::string_view, ixed::fstr_ref
TEST(CompareTests, full_compare)
{
    const char* the_band = "K.C. and the sunshine band";
    {
        fstr::fstr31 kc(the_band);
        EXPECT_EQ(kc.compare(the_band), 0);
        EXPECT_TRUE(kc == the_band);
        EXPECT_TRUE(kc == std::string(the_band));
        EXPECT_TRUE(kc == std::string_view(the_band));

        fstr::fstr31 kc2(the_band);
        EXPECT_EQ(kc.compare(kc2), 0);
        EXPECT_EQ(kc.compare(fstr::fstr_ref(kc2)), 0);
    }
}

/// Verify fstr::fstring::compare, comparing partial strings
/// when used with const char*, std::string, std::string_view, fstr::fstr_ref
TEST(CompareTests, partial_compare)
{
    const char* the_band = "K.C. and the sunshine band";
    const char* the_sunshine = "sunshine";
    {
        fstr::fstr31 kc(the_band);
        EXPECT_EQ(kc.sv().compare(13, 8, the_sunshine), 0);
        EXPECT_EQ(kc.sv().compare(13, 8, the_band, 13, 8), 0);

        fstr::fstr31 ss2(the_sunshine);
        EXPECT_EQ(kc.sv().compare(13, 8, ss2), 0);
        EXPECT_EQ(kc.sv().compare(13, 8, fstr::fstr_ref(ss2)), 0);

        std::string_view ss_view(the_sunshine);
        EXPECT_EQ(kc.sv().compare(13, 8, ss_view), 0);

        std::string ss_str(the_sunshine);
        EXPECT_EQ(kc.sv().compare(13, 8, ss_str), 0);
    }
}

/// Verify fstr::fstring::icompare
TEST(CompareTests, case_insensitive)
{
    const char* the_band = "K.C. and the sunshine band";
    const char* the_sunshine = "k.c. and the sunshine BAND";
    {
        fstr::fstr31 kc(the_band);
        fstr::fstr31 ss(the_sunshine);
        
        EXPECT_EQ(kc.icompare(ss), 0);
        EXPECT_EQ(ss.icompare(kc), 0);

        kc += "A"; // now kc is longer and thus considered "bigger"
        EXPECT_GT(kc.icompare(ss), 0);
        EXPECT_LT(ss.icompare(kc), 0);

        ss += "a"; // now they are equal again
        EXPECT_EQ(kc.icompare(ss), 0);
        EXPECT_EQ(ss.icompare(kc), 0);

        ss += "b"; // now ss is "bigger"
        EXPECT_LT(kc.icompare(ss), 0);
        EXPECT_GT(ss.icompare(kc), 0);
    }
}

TEST(CompareTests, compare_empty)
{
    fstr::fstr31 no_init;
    fstr::fstr31 empty_init("");
    fstr::fstr31 init_but_cleared("shoshana");
    init_but_cleared.clear();

    EXPECT_TRUE(no_init.empty());
    EXPECT_TRUE(empty_init.empty());
    EXPECT_TRUE(init_but_cleared.empty());

    EXPECT_EQ(no_init.size(), 0);
    EXPECT_EQ(empty_init.size(), 0);
    EXPECT_EQ(init_but_cleared.size(), 0);

    EXPECT_EQ(no_init, "");
    EXPECT_EQ(empty_init, "");
    EXPECT_EQ(init_but_cleared, "");

    std::string_view sv_no_init;
    EXPECT_EQ(no_init, sv_no_init);
    EXPECT_EQ(empty_init, sv_no_init);
    EXPECT_EQ(init_but_cleared, sv_no_init);

    std::string_view sv_empty_init("");
    EXPECT_EQ(no_init, sv_empty_init);
    EXPECT_EQ(empty_init, sv_empty_init);
    EXPECT_EQ(init_but_cleared, sv_empty_init);

    std::string_view sv_init_but_cleared("ilana");
    sv_init_but_cleared = "";
    EXPECT_EQ(no_init, sv_init_but_cleared);
    EXPECT_EQ(empty_init, sv_init_but_cleared);
    EXPECT_EQ(init_but_cleared, sv_init_but_cleared);

    EXPECT_EQ(no_init, empty_init);
    EXPECT_EQ(no_init, init_but_cleared);

    EXPECT_EQ(empty_init, no_init);
    EXPECT_EQ(empty_init, init_but_cleared);

    EXPECT_EQ(init_but_cleared, no_init);
    EXPECT_EQ(init_but_cleared, init_but_cleared);

}

#if __cplusplus >= 202002L
TEST(CompareTests, operator_spaceship)
{
    {
        // compare fstr to fstr
        fstr::fstr31 a{"a"};
        fstr::fstr15 b{"b"};
        EXPECT_TRUE(a < b);
        EXPECT_TRUE(a <= b);
        EXPECT_TRUE(a != b);
        EXPECT_FALSE(a == b);
        EXPECT_FALSE(a > b);
        EXPECT_FALSE(a >= b);

        // compare fstr_ref to fstr_ref
        fstr::fstr_ref ar{a};
        fstr::fstr_ref br{b};
        EXPECT_TRUE(ar < br);
        EXPECT_TRUE(ar <= br);
        EXPECT_TRUE(ar != br);
        EXPECT_FALSE(ar == br);
        EXPECT_FALSE(ar > br);
        EXPECT_FALSE(ar >= br);

        // compare fstr to fstr_ref
        EXPECT_TRUE(a < br);
        EXPECT_TRUE(a <= br);
        EXPECT_TRUE(a != br);
        EXPECT_FALSE(a == br);
        EXPECT_FALSE(a > br);
        EXPECT_FALSE(a >= br);

        // compare fstr_ref to fstr
        EXPECT_TRUE(ar < b);
        EXPECT_TRUE(ar <= b);
        EXPECT_TRUE(ar != b);
        EXPECT_FALSE(ar == b);
        EXPECT_FALSE(ar > b);
        EXPECT_FALSE(ar >= b);
    }
    {
        // make sure common prefix values are not considered identical
        fstr::fstr31 a{"a"};
        fstr::fstr31 aa{"aa"};
        EXPECT_TRUE(a < aa);
        EXPECT_TRUE(a <= aa);
        EXPECT_TRUE(a != aa);
        EXPECT_FALSE(a == aa);
        EXPECT_FALSE(a > aa);
        EXPECT_FALSE(a >= aa);
    }
    {
        // make sure identical values are considered identical
        fstr::fstr31 a1{"a"};
        fstr::fstr31 a2{"a"};
        EXPECT_FALSE(a1 < a2);
        EXPECT_TRUE(a1 <= a2);
        EXPECT_FALSE(a1 != a2);
        EXPECT_TRUE(a1 == a2);
        EXPECT_FALSE(a1 > a2);
        EXPECT_TRUE(a1 >= a2);
    }
}

TEST(CompareTests, operator_spaceship_combinations)
{
    // this test is mainly for ensuring that operator<=> and operator==
    // will compile of all string type combinations

    fstr::fstr31 a{"a"};
    fstr::fstr15 b{"b"};
    fstr::fstr_ref ar{a};
    fstr::fstr_ref br{b};
    std::string_view _sv("shimshon");
    std::string _str("belinson");
    const char* _c_str = "pidjamot";

// fstring_base <=> fstring_base
    EXPECT_EQ(a <=> b, std::strong_ordering::less);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);

// fstring_base <=> fstring_ref_base
    EXPECT_EQ(a <=> br, std::strong_ordering::less);
    EXPECT_FALSE(a == br);
    EXPECT_TRUE(a != br);
// fstring_ref_base <=> fstring_base
    EXPECT_EQ(br <=> a, std::strong_ordering::greater);
    EXPECT_FALSE(br == a);
    EXPECT_TRUE(br != a);

// ---

// fstring_base <=> std::string_view
    EXPECT_EQ(b <=> _sv, std::strong_ordering::less);
    EXPECT_FALSE(b == _sv);
    EXPECT_TRUE(b != _sv);
// std::string_view <=> fstring_base
    EXPECT_EQ(_sv <=> a, std::strong_ordering::greater);
    EXPECT_FALSE(_sv == a);
    EXPECT_TRUE(_sv != a);

// ---

// fstring_base <=> std::string
    EXPECT_EQ(b <=> _str, std::strong_ordering::less);
    EXPECT_FALSE(b == _str);
    EXPECT_TRUE(b != _str);
// std::string <=> fstring_base
    EXPECT_EQ(_str <=> a, std::strong_ordering::greater);
    EXPECT_FALSE(_str == a);
    EXPECT_TRUE(_str != a);

// ---

// fstring_base <=> const char*
    EXPECT_EQ(b <=> _c_str, std::strong_ordering::less);
    EXPECT_FALSE(b == _c_str);
    EXPECT_TRUE(b != _c_str);
// const char* <=> fstring_base
    EXPECT_EQ(_c_str <=> b, std::strong_ordering::greater);
    EXPECT_FALSE(_c_str == b);
    EXPECT_TRUE(_c_str != b);

// ---

// fstring_ref_base <=> fstring_ref_base
    EXPECT_EQ(ar <=> br, std::strong_ordering::less);
    EXPECT_FALSE(ar == br);
    EXPECT_TRUE(ar != br);

// ---

// fstring_ref_base <=> std::string_view
    EXPECT_EQ(ar <=> _sv, std::strong_ordering::less);
    EXPECT_FALSE(ar == _sv);
    EXPECT_TRUE(ar != _sv);
    // std::string_view <=> fstring_ref_base
    EXPECT_EQ(_sv <=> br, std::strong_ordering::greater);
    EXPECT_FALSE(_sv == br);
    EXPECT_TRUE(_sv != br);


// fstring_ref_base <=> std::string
    EXPECT_EQ(ar <=> _str, std::strong_ordering::less);
    EXPECT_FALSE(ar == _str);
    EXPECT_TRUE(ar != _str);
    // std::string <=> fstring_ref_base
    EXPECT_EQ(_str <=> br, std::strong_ordering::greater);
    EXPECT_FALSE(_str == br);
    EXPECT_TRUE(_str != br);

// ---

// fstring_ref_base <=> const char*
    EXPECT_EQ(ar <=> _c_str, std::strong_ordering::less);
    EXPECT_FALSE(ar == _c_str);
    EXPECT_TRUE(ar != _c_str);
// const char* <=> fstring_ref_base
    EXPECT_EQ(_c_str <=> ar, std::strong_ordering::greater);
    EXPECT_FALSE(_c_str == ar);
    EXPECT_TRUE(_c_str != ar);
}


TEST(CompareTests, operator_spaceship_combinations_temps)
{
    // this test is mainly for ensuring that operator<=> and operator==
    // will compile of all string type combinations given as temporary/ rvalue

    fstr::fstr31 a{"a"};
    fstr::fstr15 b{"b"};

// fstring_base <=> fstring_base
    EXPECT_EQ(fstr::fstr31{"a"} <=> fstr::fstr15{"b"}, std::strong_ordering::less);
    EXPECT_FALSE(fstr::fstr31{"a"} == fstr::fstr15{"b"});
    EXPECT_TRUE(fstr::fstr31{"a"} != fstr::fstr15{"b"});

// fstring_base <=> fstring_ref_base
    EXPECT_EQ(fstr::fstr31{"a"} <=> fstr::fstr_ref{b}, std::strong_ordering::less);
    EXPECT_FALSE(fstr::fstr31{"a"} == fstr::fstr_ref{b});
    EXPECT_TRUE(fstr::fstr31{"a"} != fstr::fstr_ref{b});

// fstring_base <=> std::string_view
    EXPECT_EQ(fstr::fstr15{"b"} <=> std::string_view("shimshon"), std::strong_ordering::less);
    EXPECT_FALSE(fstr::fstr15{"b"} == std::string_view("shimshon"));
    EXPECT_TRUE(fstr::fstr15{"b"} != std::string_view("shimshon"));

// fstring_base <=> const char*
    EXPECT_EQ(fstr::fstr15{"b"} <=> "pidjamot", std::strong_ordering::less);
    EXPECT_FALSE(fstr::fstr15{"b"} == "pidjamot");
    EXPECT_TRUE(fstr::fstr15{"b"} != "pidjamot");

// fstring_ref_base <=> fstring_base
    EXPECT_EQ(fstr::fstr_ref{b} <=> fstr::fstr31{"a"}, std::strong_ordering::greater);
    EXPECT_FALSE(fstr::fstr_ref{b} == fstr::fstr31{"a"});
    EXPECT_TRUE(fstr::fstr_ref{b} != fstr::fstr31{"a"});

// std::string_view <=> fstring_base
    EXPECT_EQ(std::string_view("shimshon") <=> fstr::fstr31{"a"}, std::strong_ordering::greater);
    EXPECT_FALSE(std::string_view("shimshon") == fstr::fstr31{"a"});
    EXPECT_TRUE(std::string_view("shimshon") != fstr::fstr31{"a"});

// const char* <=> fstring_base
    EXPECT_EQ("pidjamot" <=> fstr::fstr15{"b"}, std::strong_ordering::greater);
    EXPECT_FALSE("pidjamot" == fstr::fstr15{"b"});
    EXPECT_TRUE("pidjamot" != fstr::fstr15{"b"});

// fstring_ref_base <=> fstring_ref_base
    EXPECT_EQ(fstr::fstr_ref{a} <=> fstr::fstr_ref{b}, std::strong_ordering::less);
    EXPECT_FALSE(fstr::fstr_ref{a} == fstr::fstr_ref{b});
    EXPECT_TRUE(fstr::fstr_ref{a} != fstr::fstr_ref{b});

// fstring_ref_base <=> std::string_view
    EXPECT_EQ(fstr::fstr_ref{a} <=> std::string_view("shimshon"), std::strong_ordering::less);
    EXPECT_FALSE(fstr::fstr_ref{a} == std::string_view("shimshon"));
    EXPECT_TRUE(fstr::fstr_ref{a} != std::string_view("shimshon"));

// fstring_ref_base <=> const char*
    EXPECT_EQ(fstr::fstr_ref{a} <=> "pidjamot", std::strong_ordering::less);
    EXPECT_FALSE(fstr::fstr_ref{a} == "pidjamot");
    EXPECT_TRUE(fstr::fstr_ref{a} != "pidjamot");

    // std::string_view <=> fstring_ref_base
    EXPECT_EQ(std::string_view("shimshon") <=> fstr::fstr_ref{b}, std::strong_ordering::greater);
    EXPECT_FALSE(std::string_view("shimshon") == fstr::fstr_ref{b});
    EXPECT_TRUE(std::string_view("shimshon") != fstr::fstr_ref{b});

// const char* <=> fstring_ref_base
    EXPECT_EQ("pidjamot" <=> fstr::fstr_ref{a}, std::strong_ordering::greater);
    EXPECT_FALSE("pidjamot" == fstr::fstr_ref{a});
    EXPECT_TRUE("pidjamot" != fstr::fstr_ref{a});
}

#endif
