#include "gtest/gtest.h"
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <functional>
#include "fstring/fstring.h"
#include "fstring/fstringstream.h"

using namespace fstr;


struct fstring_ref_hasher
{
    std::size_t operator()(fstr::fstr_ref in_fixed_ref_to_hash) const noexcept
    {
        std::string_view sv{in_fixed_ref_to_hash};
        return std::hash<std::string_view>()(sv);
    }
};

/// fstr::fstr_base as key and value in std::unordered_map
TEST(Containers, UnorderedMap)
{
    std::unordered_map<fstr::fstr31, fstr::fstr31, fstr::fstr_hasher> uom;
    fstr::fstr31 s31("1st");
    uom[s31] = s31;
    EXPECT_EQ(uom.count("1st"), 1);
    EXPECT_EQ(uom.count(s31), 1);
    EXPECT_STREQ(uom["1st"].c_str(), "1st");
    EXPECT_STREQ(uom[s31].c_str(), "1st");

    fstr::fstr31 s32("2nd");
    uom[s32] = s32;
    EXPECT_EQ(uom.count("1st"), 1);
    EXPECT_EQ(uom.count(s31), 1);
    EXPECT_STREQ(uom["1st"].c_str(), "1st");
    EXPECT_STREQ(uom[s31].c_str(), "1st");

    EXPECT_EQ(uom.count("2nd"), 1);
    EXPECT_EQ(uom.count(s32), 1);
    EXPECT_STREQ(uom["2nd"].c_str(), "2nd");
    EXPECT_STREQ(uom[s32].c_str(), "2nd");
}

/// fstr::fstr_base as key and value in std::map
TEST(Containers, Map)
{
    std::map<fstr::fstr31, fstr::fstr31> m;
    fstr::fstr31 s31("1st");
    m[s31] = s31;
    EXPECT_EQ(m.count("1st"), 1);
    EXPECT_EQ(m.count(s31), 1);
    EXPECT_STREQ(m["1st"].c_str(), "1st");
    EXPECT_STREQ(m[s31].c_str(), "1st");

    fstr::fstr31 s32("2nd");
    m[s32] = s32;
    EXPECT_EQ(m.count("1st"), 1);
    EXPECT_EQ(m.count(s31), 1);
    EXPECT_STREQ(m["1st"].c_str(), "1st");
    EXPECT_STREQ(m[s31].c_str(), "1st");

    EXPECT_EQ(m.count("2nd"), 1);
    EXPECT_EQ(m.count(s32), 1);
    EXPECT_STREQ(m["2nd"].c_str(), "2nd");
    EXPECT_STREQ(m[s32].c_str(), "2nd");
}

/// fstr::fstr_base as value in std::set
TEST(Containers, Set)
{
    std::set<fstr::fstr31> s;
    fstr::fstr31 s31("1st");
    s.insert(s31);
    EXPECT_EQ(s.count("1st"), 1);
    s31 = "2nd";
    s.insert(s31);
    EXPECT_EQ(s.count("1st"), 1);
    EXPECT_EQ(s.count("2nd"), 1);

    s.insert("3rd");
    EXPECT_EQ(s.count("1st"), 1);
    EXPECT_EQ(s.count("2nd"), 1);
    EXPECT_EQ(s.count("3rd"), 1);
}

/// fstr::fstr_base as value in std::vector
TEST(Containers, Vector)
{
    std::vector<fstr::fstr31> v;
    fstr::fstr31 s31("1st");
    v.push_back(s31);
    EXPECT_STREQ(v[0].c_str(), "1st");
    s31 = "2nd";
    v.push_back(s31);
    EXPECT_STREQ(v[0].c_str(), "1st");
    EXPECT_STREQ(v[1].c_str(), "2nd");

    v.emplace_back("3rd");
    EXPECT_STREQ(v[0].c_str(), "1st");
    EXPECT_STREQ(v[1].c_str(), "2nd");
    EXPECT_STREQ(v[2].c_str(), "3rd");
}
