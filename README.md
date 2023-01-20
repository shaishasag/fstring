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
