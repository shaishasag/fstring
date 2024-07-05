#include "gtest/gtest.h"
#include "fstring.h"
#include "json_creator.h"

using namespace fixed;

TEST(CreateJson, merge_from_another)
{
    json_object_creator<31> joc1;
    joc1.append_value("mitsi", "pitsi");
    ASSERT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    
    json_object_creator<31> joc2;
    joc2.merge_values_from(joc1); // merge to empty
    ASSERT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc2.c_str(), R"|({"mitsi": "pitsi"})|");
    
    json_object_creator<63> joc3;
    joc3.append_value("Ani", "Purim");
    joc3.merge_values_from(joc2); // merge to json_object_creator that has some values
    ASSERT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc2.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc3.c_str(), R"|({"Ani": "Purim", "mitsi": "pitsi"})|");
    
    json_object_creator<15> joc_empty;
    joc3.merge_values_from(joc_empty); // merge from an empty json_object_creator
    ASSERT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc2.c_str(), R"|({"mitsi": "pitsi"})|");
    ASSERT_STREQ(joc3.c_str(), R"|({"Ani": "Purim", "mitsi": "pitsi"})|");
}

TEST(CreateJson, intertwine_obj_and_arr)
{
    json_object_creator<511> joc1;
    
    joc1.append_value("one", 1);
    auto arr1 = joc1.append_array("ARRAY!");
    auto joc2 = arr1.append_object();
    joc2.append_value("unit", "milliseconds");
    
    arr1.append_value("Lou Reed");
    
    auto joc3 = arr1.append_object();
    joc3.append_value("Part", "Time");
 
    ASSERT_STREQ(joc3.c_str(), R"|({"one": 1, "ARRAY!": [{"unit": "milliseconds"}, "Lou Reed", {"Part": "Time"}]})|");
}


TEST(CreateJson, append_json_str)
{
    json_object_creator<511> joc1;
    json_object_creator<31> joc_small;
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
    json_array_creator<31> jac_small;
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


TEST(CreateJson, prepend_json_str)
{
    json_object_creator<511> joc1;
    json_object_creator<31> joc_small;
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
    json_array_creator<31> jac_small;
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
