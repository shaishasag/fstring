#include "gtest/gtest.h"
#include <unordered_map>
#include "fstring.h"
#include "fstringstream.h"

TEST(Hashing, unordered_map)
{
    using fstring_map_t = std::unordered_map<fstr::fstr15, fstr::fstr31, fstr::fstr_hasher>;

    fstring_map_t my_map;

    my_map["1974"] = "Waterloo";
    my_map[fstr::fstr15("1976")] = fstr::fstr31("Mamma Mia");
    my_map[std::string_view("1976")] = std::string_view("Fernando");
    my_map[fstr::fstr63("1976")] = fstr::fstr63("Dancing Queen");

    EXPECT_EQ(my_map["1976"], "Dancing Queen");
}
