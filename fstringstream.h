#ifndef __fstringstream_h__
#define __fstringstream_h__

#include "fstring.h"

#include <limits.h>
#include <charconv>

// compiler does not know how to convert from fstring_base<CharT> to  fstring_ref_base<CharT>;
//template<typename CharT, typename OutT>
template<typename OutT, typename = std::enable_if_t<!std::is_convertible_v<OutT, std::string_view>>>
fixed::fstring_ref operator<<(fixed::fstring_ref fref, const OutT& to_out)
{
    if constexpr (std::is_same<OutT, bool>())
    {
        fref += to_out ? "true" : "false";
    }
    else if constexpr (std::is_same_v<OutT, fixed::fstring_ref::char_type>)
    {
        fref += to_out;
    }
    else if constexpr (std::is_integral_v<OutT>)
    {
        fref.printf(to_out);
    }
    else if constexpr (std::is_floating_point_v<OutT>)
    {
        fref.printf(to_out);
    }
    else
    {
        fref += to_out;
    }

    return fref;
}

#endif // __fstringstream_h__
