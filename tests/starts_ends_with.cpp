#include "gtest/gtest.h"
#include "fstring.h"

// untill Xcode/clang fully implements std::string_view::starts_with/ends_with
// Must supply our own implementations and test them.
// according to the standard all strings, including the empty string start and
// end with the empty string

TEST(StartWith, simple)
{
    fstr::fstr31 bn("banana");
    EXPECT_TRUE(bn.starts_with(""));
    EXPECT_TRUE(bn.starts_with("b"));
    EXPECT_TRUE(bn.starts_with("ba"));
    EXPECT_TRUE(bn.starts_with("ban"));
    EXPECT_TRUE(bn.starts_with("bana"));
    EXPECT_TRUE(bn.starts_with("banan"));
    EXPECT_TRUE(bn.starts_with("banana"));
    EXPECT_FALSE(bn.starts_with("bananab"));
    //...
    EXPECT_TRUE(bn.ends_with(""));
    EXPECT_TRUE(bn.ends_with("a"));
    EXPECT_TRUE(bn.ends_with("na"));
    EXPECT_TRUE(bn.ends_with("ana"));
    EXPECT_TRUE(bn.ends_with("nana"));
    EXPECT_TRUE(bn.ends_with("anana"));
    EXPECT_TRUE(bn.ends_with("banana"));
    EXPECT_FALSE(bn.ends_with("abanana"));

    fstr::fstr_ref bn_ref(bn);
    EXPECT_TRUE(bn_ref.starts_with(""));
    EXPECT_TRUE(bn_ref.starts_with("b"));
    EXPECT_TRUE(bn_ref.starts_with("ba"));
    EXPECT_TRUE(bn_ref.starts_with("ban"));
    EXPECT_TRUE(bn_ref.starts_with("bana"));
    EXPECT_TRUE(bn_ref.starts_with("banan"));
    EXPECT_TRUE(bn_ref.starts_with("banana"));
    EXPECT_FALSE(bn_ref.starts_with("bananab"));
    //...
    EXPECT_TRUE(bn_ref.ends_with(""));
    EXPECT_TRUE(bn_ref.ends_with("a"));
    EXPECT_TRUE(bn_ref.ends_with("na"));
    EXPECT_TRUE(bn_ref.ends_with("ana"));
    EXPECT_TRUE(bn_ref.ends_with("nana"));
    EXPECT_TRUE(bn_ref.ends_with("anana"));
    EXPECT_TRUE(bn_ref.ends_with("banana"));
    EXPECT_FALSE(bn_ref.ends_with("abanana"));
}

TEST(StartWith, empty)
{
    fstr::fstr31 bn;
    EXPECT_TRUE(bn.starts_with(""));
    EXPECT_FALSE(bn.starts_with("b"));
    EXPECT_FALSE(bn.starts_with("ba"));
    EXPECT_TRUE(bn.ends_with(""));
    EXPECT_FALSE(bn.ends_with("a"));
    EXPECT_FALSE(bn.ends_with("na"));

    fstr::fstr_ref bn_ref(bn);
    EXPECT_TRUE(bn_ref.starts_with(""));
    EXPECT_FALSE(bn_ref.starts_with("b"));
    EXPECT_FALSE(bn_ref.starts_with("ba"));
    EXPECT_TRUE(bn_ref.ends_with(""));
    EXPECT_FALSE(bn_ref.ends_with("a"));
    EXPECT_FALSE(bn_ref.ends_with("na"));
}
