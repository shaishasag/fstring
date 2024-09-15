#include "fstring.h"
#include "fstringstream.h"
#include "json_creator.h"
using namespace std::literals;

#include <vector>
#include <array>
#include <string_view>
#include <iostream>

void constructing()
{
    // constructing fstring with const char*
    const char* pompidou_c_str = "Centre Pompidou";
    fstr::fstr31 f1c = pompidou_c_str;  // copy-initialization fstring with const char*
    fstr::fstr31 f2c(pompidou_c_str);   // direct-initialization fstring with const char*
    fstr::fstr31 f3c{pompidou_c_str};   // list-initialization fstring with const char*
    
    // constructing fstring with std::string_view
    std::string_view pompidou_sv = pompidou_c_str;
    fstr::fstr31 f1sv = pompidou_sv;    // copy-initialization fstring with std::string_view
    fstr::fstr31 f2sv(pompidou_sv);     // direct-initialization fstring with std::string_view
    fstr::fstr31 f3sv{pompidou_sv};     // list-initialization fstring with std::string_view

    // constructing fstring with std::string
    std::string pompidou_str{pompidou_sv};
    fstr::fstr31 f1str = pompidou_str;    // copy-initialization fstring with std::string
    fstr::fstr31 f2str(pompidou_str);     // direct-initialization fstring with std::string
    fstr::fstr31 f3str{pompidou_str};     // list-initialization fstring with std::string
    
    // constructing std::string with fstring
    fstr::fstr31 pompidou_fixed{pompidou_c_str};
    std::string std_str2(pompidou_fixed);     // direct-initialization std::string with fstring
    std::string std_str3{pompidou_fixed};     // list-initialization std::string with fstring

    // constructing std::string_view with fstring
    std::string_view sv2(pompidou_fixed);     // direct-initialization std::string_view with fstring
    std::string_view sv3{pompidou_fixed};     // list-initialization std::string_view with fstring
}

void assigning()
{
    fstr::fstr63 f1;
    
    f1 = "bananarama";                          // assigning const char* to fstring
    f1 = std::string_view("Spandau Ballet");    // assigning std::string_view to fstring
    f1 = std::string("Spandau Ballet");         // assigning std::string to fstring
    
    std::string str1;
    str1 = f1;                                  // assigning fstring to std::string
    
    std::string_view sv1;
    sv1 = f1;                                   // assigning fstring to std::string_view
}

// json


static void create_array()
{
    fstr::    object_json_creator object;
    fstr::    array_json_creator array;

    array.append_value("Dancing Queen");
    array.append_value("Gimme", "Gimme", "Gimme");
    std::vector<float> f_vec{17.f, 18.f};
    array.extend(f_vec);
    std::vector<std::string_view> sv_vec{"Mama", "Mia"};
    array.extend(sv_vec);
    

    std::cout << array << std::endl;
}

static void create_object()
{
    fstr::object_json_creator object;

    object.append_value("People Need Love", 1972);
    object.append_value("Nina, Pretty Ballerina", 1973);
    object.append_value("Waterloo", 1974);

    std::cout << object << std::endl;
}

static void create_object_and_array()
{
    fstr::object_json_creator<1023> album;
    
    album.append_value("Artist", "ABBA");
    album.append_value("Name", "Arrival");
    album.append_value("Year", 1976);
    album.append_value("Studio", "Metronome");
    album.append_value("Time", 33.009876);

    auto personnel = album.append_array("Personnel");
    personnel.append_value("👩🏼‍👩🏼‍👦🏼‍👦🏼");
    personnel.append_value("Agnetha Fältskog");
    personnel.append_value("Anni-Frid Lyngstad");
    personnel.append_value("Björn Ulvaeus");
    personnel.append_value("Benny Andersson");

    auto tracks = album.append_object("Tracks");
    
    auto side_1 = tracks.append_array("Side 1");
    side_1.append_value("When I Kissed the Teacher");
    side_1.append_value("Dancing Queen", "My Love, My Life");
    side_1.append_value("Dum Dum Diddle", "Knowing Me, Knowing You");
    
    auto side_2 = tracks.append_array("Side 2");
    side_2.append_value("Money, Money, Money");
    std::array<std::string_view, 2> songs_array{"That's Me", "Why Did It Have to Be Me?"};
    side_2.extend(songs_array);
    std::vector<std::string_view> songs_vector{"Tiger", "Arrival"};
    side_2.extend(songs_vector);

    std::cout << std::string_view(album) << std::endl;
}

static void create()
{
    create_array();
    create_object();
    create_object_and_array();
}

static void all_types()
{
    fstr::object_json_creator object;
    
    object.append_value("True", true);
    object.append_value("False", false);
    object.append_value("float", -1.234500f);
    object.append_value("double", -5.432100f);
    object.append_value("int", (int)-17);
    object.append_value("unsigned int", (unsigned int)17);
    object.append_value("short", (short)-17);
    object.append_value("unsigned short", (unsigned short)17);
    object.append_value("long", (long)-17);
    object.append_value("unsigned long", (unsigned long)17);
    object.append_value("long long", (long long)-17);
    object.append_value("unsigned long long", (unsigned long long)17);

    object.append_value("int16_t", (int16_t)-1787);
    object.append_value("uint16_t", (uint16_t)1787);
    object.append_value("int32_t", (int32_t)-17879796);
    object.append_value("uint32_t", (uint32_t)17879796);
    object.append_value("int64_t", (int64_t)-1787979617879796);
    object.append_value("uint64_t", (uint64_t)1787979617879796);

    const char* p_c = "some dummy text";
    std::string dstr{p_c};
    std::string_view dsv{dstr};
    object.append_value("const char*", p_c);
    object.append_value("std::string", dsv);
    object.append_value("std::string_view", dsv);

    std::cout << object << std::endl;
}

int main()
{
    create();
    all_types();
    
    return 0;
}
