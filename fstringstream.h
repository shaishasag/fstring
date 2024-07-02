#ifndef __fstringstream_h__
#define __fstringstream_h__

#include "fstring.h"

#include <limits.h>
#include <charconv>
#include <iostream>

// compiler does not know how to convert from fstring_base<CharT> to  fstring_ref_base<CharT>;

template<typename ToStream, typename = std::enable_if_t<!std::is_convertible_v<ToStream, std::string_view>>>
fixed::fstring_ref operator<<(fixed::fstring_ref fref, const ToStream& thing_to_stream)
{
    if constexpr (std::is_same<ToStream, bool>())
    {
        fref += thing_to_stream ? "true" : "false";
    }
    else if constexpr (std::is_same_v<ToStream, fixed::fstring_ref::char_type>)
    {
        fref += thing_to_stream;
    }
    else if constexpr (std::is_integral_v<ToStream>)
    {
        fref.printf(thing_to_stream);
    }
    else if constexpr (std::is_floating_point_v<ToStream>)
    {
        fref.printf(thing_to_stream);
    }
    else
    {
        fref += thing_to_stream;
    }

    return fref;
}

template<typename ToChange>
void operator>>(fixed::fstring_ref fref, ToChange& thing_to_change)
{
    if constexpr (std::is_same_v<ToChange, bool>)
    {
        if (fref.starts_with("true")) {
            thing_to_change = true;
        }
        else if (fref.starts_with("false")) {
            thing_to_change = false;
        }
    }
    else if constexpr (std::is_same_v<ToChange, char>)
    {
        if (! fref.empty()) {
            thing_to_change = fref[0];
        }
    }
    else if constexpr (std::is_arithmetic_v<ToChange>)
    {
        fref.scanf(thing_to_change);
    }
}

inline std::ostream& operator<<(std::ostream& os, const fixed::fstring_ref myStr)
{
    os << std::string_view(myStr);
    return os;
}

#endif // __fstringstream_h__
