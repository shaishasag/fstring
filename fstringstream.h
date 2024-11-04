#ifndef __fstringstream_h__
#define __fstringstream_h__

/* Copy to include
#include "fstring/fstringstream.h"
*/

using namespace std::string_view_literals;


#include "fstring/fstring.h"

#include <limits.h>
#include <charconv>
#include <iostream>

// compiler does not know how to convert from fstring_base<CharT> to  fstring_ref_base<CharT>;

inline fstr::fstr_ref operator<<(fstr::fstr_ref fref, const char* in_c_str_to_stream)
{
    fref += in_c_str_to_stream;
    return fref;
}

template<typename ToStream>
inline fstr::fstr_ref operator<<(fstr::fstr_ref fref, const ToStream& thing_to_stream)
{
    if constexpr (std::is_convertible_v<ToStream, std::string_view>)
    {
        fref += thing_to_stream;
    }
    else if constexpr (std::is_same<ToStream, bool>())
    {
        fref += thing_to_stream ? "true" : "false";
    }
    else if constexpr (std::is_same_v<ToStream, fstr::fstr_ref::char_type>)
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
void operator>>(fstr::fstr_ref fref, ToChange& thing_to_change)
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

inline std::ostream& operator<<(std::ostream& os, const fstr::fstr_ref myStr)
{
    os << std::string_view(myStr);
    return os;
}

namespace fstr
{
template<typename TContainer>
static void split(std::string_view to_split_sv, std::string_view splitter, TContainer& out_splitted)
{
    auto inserter = std::back_inserter(out_splitted);
    while (!to_split_sv.empty())
    {
        auto pos = to_split_sv.find_first_of(splitter);
        if (pos == std::string_view::npos)
        {
            *inserter = to_split_sv;
            break;
        }
        else
        {
            auto sub = to_split_sv.substr(0, pos);
            if (!sub.empty())  // sub is empty if delimiter was at the beginning of to_split_sv
            {
                *inserter = sub;
            }
            to_split_sv = to_split_sv.substr(pos+splitter.size(), to_split_sv.size());
        }
    }
}

template<typename TIter>
void join(TIter begin, TIter end, std::string_view delimiter, fstr::fstr_ref out_joined)
{
    if (begin != end)
    {
        out_joined += *begin++;
        while (begin != end)
        {
            out_joined += delimiter;
            out_joined += *begin++;
        }
    }
}

struct fstr_hasher
{
    std::size_t operator()(const fstr::fstr_ref in_fixed_str_to_hash) const noexcept
    {
        return std::hash<std::string_view>()(std::string_view(in_fixed_str_to_hash));
    }
};
}

#endif // __fstringstream_h__
