#include "gtest/gtest.h"
#include "fstring.h"
#include "json_creator.h"

// tests are templated to check the two types of json creators:
// - object_json_creator & array_json_creator based on fixed::fstring
// - object_json_creator & array_json_creator based on std::string

template <typename T>
class CreateJsonTemplatedTest : public ::testing::Test {
};

// Register the pairs of types to test
// std::pair::first => object_json_creator<...>
// std::pair::second => array_json_creator<...>
typedef ::testing::Types<std::pair<fixed::object_json_creator<511>, fixed::array_json_creator<511>>,                        std::pair<dyna::object_json_creator, dyna::array_json_creator>> ObjArrPair;

TYPED_TEST_SUITE(CreateJsonTemplatedTest, ObjArrPair);

TYPED_TEST(CreateJsonTemplatedTest, SOMETHING_TYPED) {
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    obj_creator joc1;
    joc1.append_value("mitsi", "pitsi");
    EXPECT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
}


TYPED_TEST(CreateJsonTemplatedTest, merge_from_another)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    obj_creator joc1;
    joc1.append_value("mitsi", "pitsi");
    ASSERT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    
    obj_creator joc2;
    joc2.append_values_from(joc1); // merge to empty
    ASSERT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc2.c_str(), R"|({"mitsi": "pitsi"})|");
    
    obj_creator joc3;
    joc3.append_value("Ani", "Purim");
    joc3.append_values_from(joc2); // merge to fixed::object_json_creator that has some values
    ASSERT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc2.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc3.c_str(), R"|({"Ani": "Purim", "mitsi": "pitsi"})|");
    
    obj_creator joc_empty;
    joc3.append_values_from(joc_empty); // merge from an empty fixed::object_json_creator
    ASSERT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc2.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc3.c_str(), R"|({"Ani": "Purim", "mitsi": "pitsi"})|");
}

TYPED_TEST(CreateJsonTemplatedTest, intertwine_obj_and_arr)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    obj_creator joc1;
    
    joc1.append_value("one", 1);
    auto arr1 = joc1.append_array("ARRAY!");
    auto joc2 = arr1.append_object();
    joc2.append_value("unit", "milliseconds");
    
    arr1.append_value("Lou Reed");
    
    auto joc3 = arr1.append_object();
    joc3.append_value("Part", "Time");
 
    ASSERT_STREQ(joc3.c_str(), R"|({"one": 1, "ARRAY!": [{"unit": "milliseconds"}, "Lou Reed", {"Part": "Time"}]})|");
}


TYPED_TEST(CreateJsonTemplatedTest, append_json_str)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    obj_creator joc1;
    obj_creator joc_small;
    joc_small.append_value("mama", "mia");
    
    // append_json_str (which is an object) on empty object
    joc1.append_json_str("first", joc_small.c_str());
    ASSERT_STREQ(joc1.c_str(), R"|({"first": {"mama": "mia"}})|");
    
    joc_small.clear();
    // append_json_str (which is an object) on object with values
    joc_small.append_value("dancing", "queen");
    joc1.append_json_str("second", joc_small.c_str());
    ASSERT_STREQ(joc1.c_str(), R"|({"first": {"mama": "mia"}, "second": {"dancing": "queen"}})|");
    
    joc1.clear();
    fixed::array_json_creator<31> jac_small;
    jac_small.append_value("mama", "mia");
    // append_json_str (which is an array) on empty object
    joc1.append_json_str("first", jac_small.c_str());
    ASSERT_STREQ(joc1.c_str(), R"|({"first": ["mama", "mia"]})|");
    
    jac_small.clear();
    // append_json_str (which is an array) on object with values
    jac_small.append_value("dancing", "queen");
    joc1.append_json_str("second", jac_small.c_str());
    ASSERT_STREQ(joc1.c_str(), R"|({"first": ["mama", "mia"], "second": ["dancing", "queen"]})|");
}


TYPED_TEST(CreateJsonTemplatedTest, object_prepend_json_str)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    obj_creator joc1;
    obj_creator joc_small;
    joc_small.append_value("mama", "mia");
    
    // prepend_json_str (which is an object) on empty object
    joc1.prepend_json_str("first", joc_small.c_str());
    ASSERT_STREQ(joc1.c_str(), R"|({"first": {"mama": "mia"}})|");
    
    joc_small.clear();
    // prepend_json_str (which is an object) on object with values
    joc_small.append_value("dancing", "queen");
    joc1.prepend_json_str("second", joc_small.c_str());
    ASSERT_STREQ(joc1.c_str(), R"|({"second": {"dancing": "queen"}, "first": {"mama": "mia"}})|");
    
    joc1.clear();
    fixed::array_json_creator<31> jac_small;
    jac_small.append_value("mama", "mia");
    // prepend_json_str (which is an array) on empty object
    joc1.prepend_json_str("first", jac_small.c_str());
    ASSERT_STREQ(joc1.c_str(), R"|({"first": ["mama", "mia"]})|");
    
    jac_small.clear();
    // prepend_json_str (which is an array) on object with values
    jac_small.append_value("dancing", "queen");
    joc1.prepend_json_str("second", jac_small.c_str());
    ASSERT_STREQ(joc1.c_str(), R"|({"second": ["dancing", "queen"], "first": ["mama", "mia"]})|");
}



TYPED_TEST(CreateJsonTemplatedTest, array_prepend_json_str)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    arr_creator jac1;
    obj_creator joc_small;
    joc_small.append_value("mama", "mia");
    
    // prepend_json_str (which is an object) on empty object
    jac1.prepend_json_str(joc_small.c_str());
    ASSERT_STREQ(jac1.c_str(), R"|([{"mama": "mia"}])|");
    
    joc_small.clear();
    // prepend_json_str (which is an object) on object with values
    joc_small.append_value("dancing", "queen");
    jac1.prepend_json_str(joc_small.c_str());
    ASSERT_STREQ(jac1.c_str(), R"|([{"dancing": "queen"}, {"mama": "mia"}])|");
    
    jac1.clear();
    arr_creator jac_small;
    jac_small.append_value("mama", "mia");
    // prepend_json_str (which is an array) on empty object
    jac1.prepend_json_str(jac_small.c_str());
    ASSERT_STREQ(jac1.c_str(), R"|([["mama", "mia"]])|");
    
    jac_small.clear();
    // prepend_json_str (which is an array) on object with values
    jac_small.append_value("dancing", "queen");
    jac1.prepend_json_str(jac_small.c_str());
    ASSERT_STREQ(jac1.c_str(), R"|([["dancing", "queen"], ["mama", "mia"]])|");
}

TYPED_TEST(CreateJsonTemplatedTest, object_append_values_from)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    obj_creator joc1;
    obj_creator joc_small;
    joc1.append_values_from(joc_small);
    ASSERT_STREQ(joc1.c_str(), R"|({})|"); // append empty obj to to empty obj

    joc_small.append_value("mama", "mia");
    joc1.append_values_from(joc_small);
    ASSERT_STREQ(joc1.c_str(), R"|({"mama": "mia"})|");

    joc_small.clear();
    joc_small.append_value("forget", "me not");
    joc1.append_values_from(joc_small);
    ASSERT_STREQ(joc1.c_str(), R"|({"mama": "mia", "forget": "me not"})|");
}

TYPED_TEST(CreateJsonTemplatedTest, object_prepend_values_from)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    obj_creator joc1;
    obj_creator joc_small;
    joc1.prepend_values_from(joc_small);
    ASSERT_STREQ(joc1.c_str(), R"|({})|"); // prepend empty obj to to empty obj

    joc_small.append_value("mama", "mia");
    joc1.prepend_values_from(joc_small);
    ASSERT_STREQ(joc1.c_str(), R"|({"mama": "mia"})|");

    joc_small.clear();
    joc_small.append_value("forget", "me not");
    joc1.prepend_values_from(joc_small);
    ASSERT_STREQ(joc1.c_str(), R"|({"forget": "me not", "mama": "mia"})|");
}


TYPED_TEST(CreateJsonTemplatedTest, array_append_values_from)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    arr_creator jac1;
    arr_creator jac_small;
    jac1.append_values_from(jac_small);
    ASSERT_STREQ(jac1.c_str(), R"|([])|"); // append empty obj to to empty obj

    jac_small.append_value("mama", "mia");
    jac1.append_values_from(jac_small);
    ASSERT_STREQ(jac1.c_str(), R"|(["mama", "mia"])|");

    jac_small.clear();
    jac_small.append_value("forget", "me not");
    jac1.append_values_from(jac_small);
    ASSERT_STREQ(jac1.c_str(), R"|(["mama", "mia", "forget", "me not"])|");
}

TYPED_TEST(CreateJsonTemplatedTest, array_prepend_values_from)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    arr_creator jac1;
    arr_creator jac_small;
    jac1.prepend_values_from(jac_small);
    ASSERT_STREQ(jac1.c_str(), R"|([])|"); // append empty obj to to empty obj

    jac_small.append_value("mama", "mia");
    jac1.prepend_values_from(jac_small);
    ASSERT_STREQ(jac1.c_str(), R"|(["mama", "mia"])|");

    jac_small.clear();
    jac_small.append_value("forget", "me not");
    jac1.prepend_values_from(jac_small);
    ASSERT_STREQ(jac1.c_str(), R"|(["forget", "me not", "mama", "mia"])|");
}


TYPED_TEST(CreateJsonTemplatedTest, append_value_variadric)
{
    using obj_creator = typename TypeParam::first_type;
    using arr_creator = typename TypeParam::second_type;

    arr_creator jac1;
    jac1.append_value(17,
                      "18",
                      std::string("19"),
                      std::string_view("20"),
                      fixed::fstring31("21"));
    ASSERT_STREQ(jac1.c_str(), R"|([17, "18", "19", "20", "21"])|");
    
    obj_creator joc1;
    joc1.append_value("17", 17,
                      fixed::fstring31("19"), std::string("19"),
                      std::string("20"), std::string_view("20"),
                      std::string_view("21"), fixed::fstring31("21"));
    ASSERT_STREQ(joc1.c_str(), R"|({"17": 17, "19": "19", "20": "20", "21": "21"})|");
}
