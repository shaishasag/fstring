#include "fstring.h"
using namespace std::literals;

void constructing()
{
    // constructing fstring with const char*
    const char* pompidou_c_str = "Centre Pompidou";
    fixed::fstring31 f1c = pompidou_c_str;  // copy-initialization fstring with const char*
    fixed::fstring31 f2c(pompidou_c_str);   // direct-initialization fstring with const char*
    fixed::fstring31 f3c{pompidou_c_str};   // list-initialization fstring with const char*
    
    // constructing fstring with std::string_view
    std::string_view pompidou_sv = pompidou_c_str;
    fixed::fstring31 f1sv = pompidou_sv;    // copy-initialization fstring with std::string_view
    fixed::fstring31 f2sv(pompidou_sv);     // direct-initialization fstring with std::string_view
    fixed::fstring31 f3sv{pompidou_sv};     // list-initialization fstring with std::string_view

    // constructing fstring with std::string
    std::string pompidou_str{pompidou_sv};
    fixed::fstring31 f1str = pompidou_str;    // copy-initialization fstring with std::string
    fixed::fstring31 f2str(pompidou_str);     // direct-initialization fstring with std::string
    fixed::fstring31 f3str{pompidou_str};     // list-initialization fstring with std::string
    
    // constructing std::string with fstring
    fixed::fstring31 pompidou_fixed{pompidou_c_str};
    std::string std_str2(pompidou_fixed);     // direct-initialization std::string with fstring
    std::string std_str3{pompidou_fixed};     // list-initialization std::string with fstring

    // constructing std::string_view with fstring
    std::string_view sv2(pompidou_fixed);     // direct-initialization std::string_view with fstring
    std::string_view sv3{pompidou_fixed};     // list-initialization std::string_view with fstring
}

void assigning()
{
    fixed::fstring63 f1;
    
    f1 = "bananarama";                          // assigning const char* to fstring
    f1 = std::string_view("Spandau Ballet");    // assigning std::string_view to fstring
    f1 = std::string("Spandau Ballet");         // assigning std::string to fstring
    
    std::string str1;
    str1 = f1;                                  // assigning fstring to std::string
    
    std::string_view sv1;
    sv1 = f1;                                   // assigning fstring to std::string_view
}
