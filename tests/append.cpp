#include "gtest/gtest.h"
#include "fstring.h"

using namespace fstr;

// operator+= with all kind of strings
TEST(AppendTests, operator_plus_equal)
{

    std::string big_b{"B"};
    std::string_view small_a{"a"};
    fstr::fstr15 small_n{"n"};
    fstr::fstr_ref small_n_ref{small_n};
    const char big_R = 'R';
    const char* ama = "ama";

    {
        // fstring_base::operator+=
        fstr::fstr127 f1;

        f1 += big_b;    // "B"
        f1 += small_a;  // "Ba"
        f1 += small_n;  // "Ban"
        f1 += small_a;  // "Bana"
        f1 += small_n;  // "Banan"
        f1 += 'a';      // "Banana"
        f1 += big_R;    // "BananaR"
        f1 += ama;      // "BananaRama"
        EXPECT_EQ(f1, "BananaRama");
    }

    {
        // fstring_base_ref::operator+=
        fstr::fstr127 f1;
        fstr::fstr_ref f1_ref(f1);

        f1_ref += big_b;    // "B"
        f1_ref += small_a;  // "Ba"
        f1_ref += small_n;  // "Ban"
        f1_ref += small_a;  // "Bana"
        f1_ref += small_n;  // "Banan"
        f1_ref += 'a';      // "Banana"
        f1_ref += big_R;    // "BananaR"
        f1_ref += ama;      // "BananaRama"
        EXPECT_EQ(f1_ref, "BananaRama");
    }
}

// append with all kind of strings
TEST(AppendTests, append)
{

    std::string big_b{"B"};
    std::string_view small_a{"a"};
    fstr::fstr15 small_n{"n"};
    fstr::fstr_ref small_n_ref{small_n};
    const char big_R = 'R';
    const char* ama = "amama";

    {
        // fstring_base::operator+=
        fstr::fstr127 f1;

        f1.append(big_b);    // "B"
        f1.append(small_a);  // "Ba"
        f1.append(small_n);  // "Ban"
        f1.append(small_a);  // "Bana"
        f1.append(small_n);  // "Banan"
        f1.append('a');      // "Banana"
        f1.append(1, big_R);    // "BananaR"
        f1.append(ama, 3);      // "BananaRama"
        f1.append("123");      // "BananaRama123"
        EXPECT_EQ(f1, "BananaRama123");
    }

    {
        // fstring_base_ref::operator+=
        fstr::fstr127 f1;
        fstr::fstr_ref f1_ref(f1);

        f1_ref.append(big_b);    // "B"
        f1_ref.append(small_a);  // "Ba"
        f1_ref.append(small_n);  // "Ban"
        f1_ref.append(small_a);  // "Bana"
        f1_ref.append(small_n);  // "Banan"
        f1_ref.append('a');      // "Banana"
        f1_ref.append(1, big_R);    // "BananaR"
        f1_ref.append(ama, 3);      // "BananaRama"
        f1_ref.append("123");      // "BananaRama123"
        EXPECT_EQ(f1_ref, "BananaRama123");
    }
}
