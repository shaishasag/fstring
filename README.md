# fstring
Fixed capacity C++ string class

**fstring** is C++17 fixed capacity string class.

For the most part **fstring** follows the std::string and std::string_view interface.

    #include <iostream>
    #include "fstring.h"
    
    int main(int argc, char** argv)
    {
        fixed::fstring31 fstr("Hello fstring");
        std::cout << fstr << std::endl;
        
        return 0;
    }

fstring:
* never allocates memory
* is memcopy-able
* supports most std::string and std::string_view interface

Associated class **fstring_ref** allows passing/returning **fstring** of any size to function so that the function does not need to be templated on the size of **fstring**.


    #include <iostream>
    #include "fstring.h"
    
    fixed::fstring_ref func(fixed::fstring_ref f_string)
    {
        // do something with f_string
        return f_string;
    }

    fixed::fstring15 f15;
    fixed::fstring31 f31;
    fixed::fstring63 f63;

    // any size fstring can be passed to func and fstring_ref is returned
    std::cout << func(f15) << std::endl;
    std::cout << func(f31) << std::endl;
    std::cout << func(f63) << std::endl;
