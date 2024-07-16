#include <stdlib.h>
#include <iostream>

#include "fstring.h"
#include "fstringstream.h"

int main(int argc, char** argv)
{
    std::cout << "sizeof(fixed::fstring_base<0, char>) = " << sizeof(fixed::fstring_base<0, char>)  << std::endl;
    std::cout << "sizeof(fixed::fstring15) = " << sizeof(fixed::fstring15)  << std::endl;
    std::cout << "    alignof(fixed::fstring15) = " << fixed::fstring15::_alignof()  << std::endl;
    std::cout << "sizeof(fixed::fstring31) = " << sizeof(fixed::fstring31)  << std::endl;
    std::cout << "    alignof(fixed::fstring31) = " << alignof(fixed::fstring31)  << std::endl;
    std::cout << "sizeof(fixed::fstring63) = " << sizeof(fixed::fstring63)  << std::endl;
    std::cout << "    alignof(fixed::fstring63) = " << alignof(fixed::fstring63)  << std::endl;
    std::cout << "sizeof(fixed::fstring_ref) = " << sizeof(fixed::fstring_ref)  << std::endl;
    std::cout << "    alignof(fixed::fstring_ref) = " << alignof(fixed::fstring_ref)  << std::endl;

    constexpr fixed::fstring31 fstr("Hello fstring");
    std::cout << std::string_view(fstr) << std::endl;

    return 0;
}
