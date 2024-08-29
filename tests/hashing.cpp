#include "gtest/gtest.h"
#include <unordered_map>
#include "fstring.h"
#include "fstringstream.h"

TEST(Hashing, unordered_map)
{
    using fstring_map_t = std::unordered_map<fixed::fstring15, fixed::fstring31, fixed::fstring_hasher>;

    fstring_map_t my_map;

    my_map["1974"] = "Waterloo";
    my_map[fixed::fstring15("1976")] = fixed::fstring31("Mamma Mia");
    my_map[std::string_view("1976")] = std::string_view("Fernando");
    my_map[fixed::fstring63("1976")] = fixed::fstring63("Dancing Queen");

    EXPECT_EQ(my_map["1976"], "Dancing Queen");
}
