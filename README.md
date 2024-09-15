# fstring
Fixed capacity C++ string class.

## About
**fstr::fstring** is C++17 fixed capacity string class.

For the most part **fstring** follows the std::string and std::string_view interface.

    #include <iostream>
    #include "fstring/fstring.h"

    int main(int argc, char** argv)
    {
        fstr::fstr31 fstr("Hello fstring");
        std::cout << fstr << std::endl;

        return 0;
    }

## Details
### fstring:
* Never allocates memory, so can be used in time-critical code.
* Is memcopy-able.
* Supports most std::string and std::string_view interface.
* Automatically converted to string_view.
* Implements some additional functionality not found in std::string and std::string_view:
    + trim_front
    + trim_back
    + trim
    + tolower
    + toupper
    + erase_all_of
    + erase_all_not_of

### fstring_ref:

Associated class **fstring_ref** allows passing/returning **fstring** of any size to/from a function so that the function does not need to be templated on the size of **fstring**.


    #include <iostream>
    #include "fstring.h"

    fstr::fstring_ref func(fstr::fstring_ref f_string)
    {
        // do something with f_string
        return f_string;
    }

    fstr::fstr15 f15;
    fstr::fstr31 f31;
    fstr::fstr63 f63;

    // fstring of any size can be passed to func
    std::cout << func(f15) << std::endl;
    std::cout << func(f31) << std::endl;
    std::cout << func(f63) << std::endl;

## Examples
See examples/examples.cpp.

## Tests

Extensive test were implemented with googletest.

## Cross platform (tested platforms)
+ MacOS Xcode 14.0+

## Authors

* **Shai Shasag**

## License

This project is licensed under the BSD-3-Clause license - see the [LICENSE](LICENSE) file for details

