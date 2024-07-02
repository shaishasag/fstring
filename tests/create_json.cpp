#include "gtest/gtest.h"
#include "fstring.h"
#include "json_creator.h"

using namespace fixed;

TEST(CreateJson, merge_from_another)
{
    fstring31 s1;
    json_object_creator joc1(s1);
    joc1.append_value("mitsi", "pitsi");
    EXPECT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    
    fstring31 s2;
    json_object_creator joc2(s2);
    joc2.merge_values_from(joc1); // merge to empty
    EXPECT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    EXPECT_STREQ(joc2.c_str(), R"|({"mitsi": "pitsi"})|");
    
    fstring63 s3;
    json_object_creator joc3(s3);
    joc3.append_value("Ani", "Purim");
    joc3.merge_values_from(joc2); // merge to json_object_creator that has some values
    EXPECT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    EXPECT_STREQ(joc2.c_str(), R"|({"mitsi": "pitsi"})|");
    EXPECT_STREQ(joc3.c_str(), R"|({"Ani": "Purim", "mitsi": "pitsi"})|");
    
    
    fstring15 s4;
    json_object_creator joc_empty(s4);
    joc3.merge_values_from(joc_empty); // merge from an empty json_object_creator
    EXPECT_STREQ(joc1.c_str(), R"|({"mitsi": "pitsi"})|");
    EXPECT_STREQ(joc2.c_str(), R"|({"mitsi": "pitsi"})|");
    EXPECT_STREQ(joc3.c_str(), R"|({"Ani": "Purim", "mitsi": "pitsi"})|");
}
