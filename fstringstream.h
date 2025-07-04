#ifndef __fstringstream_h__
#define __fstringstream_h__

/* Copy to include
#include "fstring/fstringstream.h"
*/

#include "fstring/fstring.h"

#include <limits.h>
#include <charconv>
#include <iostream>

// compiler does not know how to convert from fstring_base<CharT> to  fstring_ref_base<CharT>

inline fstr::fstr_ref operator<<(fstr::fstr_ref fref, const char* in_c_str_to_stream)
{
    fref += in_c_str_to_stream;
    return fref;
}

template<typename ToStream>
inline fstr::fstr_ref operator<<(fstr::fstr_ref fref, const ToStream& thing_to_stream)
{
    if constexpr (std::is_convertible_v<ToStream, std::string_view>
                  || std::is_same_v<ToStream, fstr::fstr_ref::char_type>)
    {
        fref += thing_to_stream;
    }
    else if constexpr (IsPrintfable<ToStream>)
    {
        fref.printf(thing_to_stream);
    }

    return fref;
}

template<typename ToChange>
void operator>>(fstr::fstr_ref fref, ToChange& thing_to_change)
{
    if constexpr (std::is_same_v<ToChange, bool>)
    {
        if (fref.sv().starts_with("true")) {
            thing_to_change = true;
        }
        else if (fref.sv().starts_with("false")) {
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
struct fstr_hasher
{
    std::size_t operator()(const fstr::fstr_ref in_fixed_str_to_hash) const noexcept
    {
        return std::hash<std::string_view>()(std::string_view(in_fixed_str_to_hash));
    }
};

/// Splits a std::string_view using a string delimiter into a vector of string_views.
///
/// This function scans the input string for all non-overlapping occurrences of the specified delimiter
/// and returns substrings between those delimiters as std::vector<std::string_view>.
///
/// Empty tokens are preserved by default — for example:
/// - `"a,,b"` with delimiter `","` → `["a", "", "b"]`
/// - `"::"` with delimiter `"::"` → `["", ""]`
///
/// If `skip_empty` is true, then any empty substrings are excluded from the result.
///
/// @param input The std::string_view to split.
/// @param delim The delimiter string used to split the input. Must not be empty.
/// @param skip_empty If true, skips over any empty tokens in the result. Defaults to false.
/// @return std::vector<std::string_view> representing the tokens between delimiters.
///
/// @throws std::invalid_argument if `delim` is empty.
///
/// @note This function does not allocate new strings — all views refer to the memory of the original `input`.
///       Ensure that `input` remains alive for as long as the result is used.
///
/// @see std::string_view

inline std::vector<std::string_view> split(std::string_view input,
                                    std::string_view delim,
                                    bool skip_empty=false)
{
    if (delim.empty()) {
        throw std::invalid_argument("Delimiter must not be empty");
    }

    std::vector<std::string_view> result;

    size_t start = 0;
    while (start <= input.size())
    {
        size_t end = input.find(delim, start);
        std::string_view token = (end == std::string_view::npos)
                                 ? input.substr(start)
                                 : input.substr(start, end - start);

        if (!skip_empty || !token.empty())
            result.emplace_back(token);

        if (end == std::string_view::npos) break;
        start = end + delim.size();
    }

    return result;
}

// Check if T has a .reserve(size_t) method
template <typename T>
constexpr bool has_reserve_v = requires(T t, size_t n) {
    t.reserve(n);
};


/// Joins a sequence of `std::string_view` elements using the given delimiter,
/// and stores the result in the provided `fstr::fstr_ref or std::string result`.
///
/// This function concatenates all elements in `parts`, inserting `delim` between them.
/// The `result` string is not cleared before appending. If the delimiter is empty,
/// the parts are simply concatenated.
///
/// @param parts A vector of `std::string_view` to join.
/// @param delim A delimiter to insert between elements. May be empty.
/// @param result a `str::fstr_ref or std::string` that will be appended with the result.

template<typename TOutput>
requires std::is_same_v<TOutput, std::string> || std::is_convertible_v<TOutput, fstr::fstr_ref>
void join(const std::vector<std::string_view>& parts,
          std::string_view delim,
          TOutput& result)
{
    if (parts.empty()) return;

    if constexpr (has_reserve_v<TOutput>)
    {
        // Precompute total size for efficient memory reservation
        size_t total_size = result.size();
        for (const auto& part : parts)
        {
            total_size += part.size();
        }
        total_size += delim.size() * (parts.size() - 1);
    
        result.reserve(total_size);
    }
    
    result += parts[0];
    for (size_t i = 1; i < parts.size() && result.max_size() > result.size(); ++i)
    {
        result += delim;
        result += parts[i];
    }
}

}

#endif // __fstringstream_h__
