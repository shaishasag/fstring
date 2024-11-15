#include "fstring.h"
#include "fstringstream.h"

using namespace std::literals;

#include <sys/stat.h>
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


// for README.md:
fstr::fstr_ref func(fstr::fstr_ref f_string)
{
    // do something with f_string
    return f_string;
}

void call_chmod()
{
    fstr::fstr255 some_path("/usr/local/bin/exec");
    chmod(some_path.c_str(), 0766);
}

void README_example_1()
{
    fstr::fstr15 f15("short");
    fstr::fstr31 f31("medium");
    fstr::fstr63 f63("largish");

    // fstring of any size can be passed to func
    std::cout << func(f15) << std::endl;
    std::cout << func(f31) << std::endl;
    std::cout << func(f63) << std::endl;
}

void README_example_2()
{
    fstr::fstr31 hello_fs("hello");

    if (hello_fs.sv().starts_with("He")) {}
    if (hello_fs.sv().ends_with('o')) {}
    if (hello_fs.sv().find('l') != std::string_view::npos) {}
    if (hello_fs.sv().rfind("ll") != std::string_view::npos) {}
    if (hello_fs.sv().find_first_of('l') != std::string_view::npos) {}
    if (hello_fs.sv().find_last_of("ll") != std::string_view::npos) {}
    if (hello_fs.sv().find_first_not_of("xyz") != std::string_view::npos) {}
    if (hello_fs.sv().find_last_not_of("abc") != std::string_view::npos) {}
}

int main()
{
    constructing();
    assigning();
    README_example_1();
    README_example_2();

    return 0;
}
