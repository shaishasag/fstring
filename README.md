# fstring
Fixed capacity C++ string class.

## About
**fstr::fstring** is C++20 fixed capacity string class. 
C++17 compatible code is avaliable in branch "C++17".

For the most part **fstring** follows the std::string and std::string_view interface.

```source.c++
    #include <iostream>
    #include "fstring/fstring.h"

    int main(int argc, char** argv)
    {
        fstr::fstr31 fstr("Hello fstring");
        std::cout << fstr << std::endl;

        return 0;
    }
```

## Details
### fstring:
* Never allocates memory, so can be used in time-critical code.
* Is memcopy-able: can be copied with memcpy.

* Supports most std::string and std::string_view interface.
    Use fstr::fstr_base::**sv()** to access the following std::string_view functions:
    
```source.c++
    fstr::fstr31 hello_fs("hello");

    if (hello_fs.sv().starts_with("He")) {}
    if (hello_fs.sv().ends_with('o')) {}
    if (hello_fs.sv().find('l') != std::string_view::npos) {}
    if (hello_fs.sv().rfind("ll") != std::string_view::npos) {}
    if (hello_fs.sv().find_first_of('l') != std::string_view::npos) {}
    if (hello_fs.sv().find_last_of("ll") != std::string_view::npos) {}
    if (hello_fs.sv().find_first_not_of("xyz") != std::string_view::npos) {}
    if (hello_fs.sv().find_last_not_of("abc") != std::string_view::npos) {}
```

* Automatically converts to string_view.
* Implements some additional functionality not found in std::string and std::string_view:
    + trim_front
    + trim_back
    + trim
    + tolower
    + toupper
    + erase_all_of
    + erase_all_not_of
    + printf
    + scanf


### always maintains terminating '\0', so can be passed to functions like chmod:

```source.c++
void call_chmod()
{
    fstr::fstr255 some_path("/usr/local/bin/exec");
    chmod(some_path.c_str(), 0766);
}
```

### fstring_ref:
Associated class **fstring_ref** allows passing/returning **fstring** of any size to/from a function so that the function does not need to be templated on the size of **fstring**.

```source.c++
    #include <iostream>
    #include "fstring.h"

    fstr::fstr_ref func(fstr::fstr_ref f_string)
    {
        // do something with f_string
        return f_string;
    }

    fstr::fstr15 f15("short");
    fstr::fstr31 f31("medium");
    fstr::fstr63 f63("largish");

    // fstring of any size can be passed to func
    std::cout << func(f15) << std::endl;
    std::cout << func(f31) << std::endl;
    std::cout << func(f63) << std::endl;
```

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

