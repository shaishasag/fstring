#include <iostream>

#include "gtest/gtest.h"
#include "fstring.h"


int main(int argc, char** argv)
{
    std::cout << "sizeof(fixed::fstring_base<0, char>) = " << sizeof(fixed::fstring_base<0, char>)  << std::endl;
    std::cout << "sizeof(fixed::fstring15) = " << sizeof(fixed::fstring15)  << std::endl;
    std::cout << "sizeof(fixed::fstring31) = " << sizeof(fixed::fstring31)  << std::endl;
    std::cout << "sizeof(fixed::fstring63) = " << sizeof(fixed::fstring63)  << std::endl;
    std::cout << "sizeof(fixed::fstring_ref) = " << sizeof(fixed::fstring_ref)  << std::endl;

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

