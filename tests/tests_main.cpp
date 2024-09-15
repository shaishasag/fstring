#include <iostream>

#include "gtest/gtest.h"
#include "fstring.h"


int main(int argc, char** argv)
{
    std::cout << "sizeof(fstr::fstring_base<0, char>) = " << sizeof(fstr::fstring_base<0, char>)  << std::endl;
    std::cout << "sizeof(fstr::fstr15) = " << sizeof(fstr::fstr15)  << std::endl;
    std::cout << "sizeof(fstr::fstr31) = " << sizeof(fstr::fstr31)  << std::endl;
    std::cout << "sizeof(fstr::fstr63) = " << sizeof(fstr::fstr63)  << std::endl;
    std::cout << "sizeof(fstr::fstr_ref) = " << sizeof(fstr::fstr_ref)  << std::endl;

    testing::InitGoogleTest(&argc, argv);

    int retVal = RUN_ALL_TESTS();
    return retVal;
}

