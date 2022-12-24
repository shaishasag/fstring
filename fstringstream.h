#ifndef __fstringstream_h__
#define __fstringstream_h__

#include "fstring.h"

#include <limits.h>
#include <charconv>

// compiler does not know how to convert from fstring_base<CharT> to  fstring_ref_base<CharT>;
//template<typename CharT, typename OutT>
template<typename OutT>
fixed::fstring_ref operator<< (fixed::fstring_ref fref, OutT to_out)
{
    if constexpr (std::is_same<OutT, bool>())
    {
        fref += to_out ? "true" : "false";
    }
    else if constexpr (std::is_same<OutT, fixed::fstring_ref::char_type>())
    {
        fref += to_out;
    }
    else if constexpr (std::is_integral_v<OutT>)
    {
        constexpr size_t num_integral_digits = 20;
        char buff[num_integral_digits+1];
        std::to_chars_result tcr = std::to_chars(buff,
                                                 buff+num_integral_digits,
                                                 to_out);
        *tcr.ptr = '\0';
        fref += buff;
    }
    else if constexpr (std::is_floating_point_v<OutT>)
    {
        constexpr size_t num_float_digits = 3 + DBL_MANT_DIG - DBL_MIN_EXP;
        char buff[num_float_digits+1];
        std::to_chars_result tcr = std::to_chars(buff,
                                                 buff+num_float_digits,
                                                 to_out,
                                                 std::chars_format::fixed);
        *tcr.ptr = '\0';
        fref += buff;
    }
    else
    {
        fref += to_out;
    }

    return fref;
}

#endif // __fstringstream_h__
