#ifndef __fstringstream_h__
#define __fstringstream_h__

/* Copy to include
#include "fstring/fstringstream.h"
*/

#include "fstring/fstring.h"

#include <limits.h>
#include <charconv>
#include <iostream>
#include <type_traits>
#include <utility>

// compiler does not know how to convert from fstring_base<CharT> to  fstring_ref_base<CharT>

namespace fstr
{

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

// Streaming a wrap_me writes TOpen, then the value, then TClose. The value is
// held by reference, so a wrap_me must not outlive the full-expression it was
// created in - which is the normal usage: stream << quote_me(x).
// TClose defaults to TOpen, so a symmetric wrapper only needs the one character:
// wrap_me<'#', std::string_view> is the same as wrap_me<'#', std::string_view, '#'>.
template<char TOpen, typename ToWrap, char TClose = TOpen>
class wrap_me
{
public:
    explicit wrap_me(const ToWrap& in_to_wrap)
    : m_to_wrap(in_to_wrap)
    {
    }

    static constexpr char opening_char{TOpen};
    static constexpr char closing_char{TClose};

    const ToWrap& m_to_wrap;
};

// The named wrappers are aliases of wrap_me where the compiler supports CTAD
// through an alias template - C++20's P1814 - and derived classes otherwise.
// Both forms spell the same thing and support the same usage; only the alias
// form needs P1814, because fstr::quote_me(x) with no template argument list
// has to deduce ToWrap through the alias.
// The feature test is on __cpp_deduction_guides rather than __cplusplus on
// purpose: P1814 is a core C++20 feature, but compilers shipped it long after
// they began claiming C++20 - Apple clang 16 still reports 201703 even under
// -std=c++23, so keying off __cplusplus would break that build.
#if defined(__cpp_deduction_guides) && __cpp_deduction_guides >= 201907L

template<typename ToWrap> using quote_me        = wrap_me<'"',  ToWrap>;
template<typename ToWrap> using single_quote_me = wrap_me<'\'', ToWrap>;
template<typename ToWrap> using brace_me        = wrap_me<'[',  ToWrap, ']'>;
template<typename ToWrap> using curly_brace_me  = wrap_me<'{',  ToWrap, '}'>;
template<typename ToWrap> using angle_brace_me  = wrap_me<'<',  ToWrap, '>'>;
template<typename ToWrap> using parenthesize_me = wrap_me<'(',  ToWrap, ')'>;

#else

// Each derived wrapper needs its own deduction guide: without one, CTAD would
// treat the inherited constructor's parameter as a plain rvalue reference -
// ToWrap is declared by the class template, so it is not a forwarding reference
// there - and lvalue arguments would fail to deduce.
#define FSTR_DECLARE_WRAPPER(WRAPPER_NAME, OPENING_CHAR, CLOSING_CHAR)      \
template<typename ToWrap>                                                   \
class WRAPPER_NAME : public wrap_me<OPENING_CHAR, ToWrap, CLOSING_CHAR>     \
{                                                                           \
public:                                                                     \
    using wrap_me<OPENING_CHAR, ToWrap, CLOSING_CHAR>::wrap_me;             \
};                                                                          \
template<typename ToWrap>                                                   \
WRAPPER_NAME(ToWrap&&) -> WRAPPER_NAME<std::decay_t<ToWrap>>

FSTR_DECLARE_WRAPPER(quote_me,        '"',  '"');
FSTR_DECLARE_WRAPPER(single_quote_me, '\'', '\'');
FSTR_DECLARE_WRAPPER(brace_me,        '[',  ']');
FSTR_DECLARE_WRAPPER(curly_brace_me,  '{',  '}');
FSTR_DECLARE_WRAPPER(angle_brace_me,  '<',  '>');
FSTR_DECLARE_WRAPPER(parenthesize_me, '(',  ')');

#undef FSTR_DECLARE_WRAPPER

#endif // __cpp_deduction_guides >= 201907L

// For characters with no named wrapper, when the value type should be deduced:
//     fstr << fstr::wrap<'|'>(value);        // both characters are '|'
//     fstr << fstr::wrap<'<', '>'>(value);   // asymmetric
// The characters stay adjacent here, unlike in wrap_me itself, so that TClose can
// be given without also spelling out the value type. Naming wrap_me directly and
// leaving TClose to default needs the type: wrap_me<'#', std::string_view>.
template<char TOpen, char TClose = TOpen, typename ToWrap>
inline wrap_me<TOpen, ToWrap, TClose> wrap(const ToWrap& in_to_wrap)
{
    return wrap_me<TOpen, ToWrap, TClose>(in_to_wrap);
}

// Only declared, never defined - used solely to ask "does T derive from some
// wrap_me?" inside the concept below.
template<char TOpen, typename ToWrap, char TClose>
void is_wrap_me_probe(const wrap_me<TOpen, ToWrap, TClose>&);

template<typename TWrapper>
concept IsWrapMe = requires (const TWrapper& in_wrapper) { is_wrap_me_probe(in_wrapper); };

// Note this takes the wrapper as a deduced parameter constrained by IsWrapMe,
// rather than as a wrap_me<TOpen, ToWrap, TClose> pattern. With the pattern, a
// derived wrapper such as quote_me needs a derived-to-base conversion, which
// ranks below the exact match that the generic operator<<(fstr_ref, const
// ToStream&) above offers - so the generic one would win and silently write
// nothing, since a wrapper matches none of the branches in its if constexpr
// chain. Deducing the wrapper type makes this an exact match too, and the
// constraint then makes it the more specialized candidate.
template<IsWrapMe TWrapper>
inline fstr::fstr_ref operator<<(fstr::fstr_ref fref, const TWrapper& thing_to_wrap)
{
    fref << TWrapper::opening_char << thing_to_wrap.m_to_wrap << TWrapper::closing_char;
    return fref;
}

// Same for any other stream, so long as 'stream << char << value << char'
// compiles for it - std::ostream, std::ostringstream, or a user's own type.
// TStream is a forwarding reference so that both lvalue streams (std::cout) and
// prvalue handles bind, and decltype(auto) propagates whatever the underlying
// chain returns: a reference for std::ostream, a value for a handle.
// A stream that cannot accept the wrapped type fails to compile inside, which is
// intended. Streams convertible to fstr_ref are excluded so this never competes
// with the overload above - without that, an already-exact fstr_ref left
// operand makes the two candidates ambiguous, since each is more specialized in
// a different parameter.
template<typename TStream, IsWrapMe TWrapper>
requires (! std::is_convertible_v<TStream, fstr::fstr_ref>)
inline decltype(auto) operator<<(TStream&& stream, const TWrapper& thing_to_wrap)
{
    return std::forward<TStream>(stream)
                << TWrapper::opening_char << thing_to_wrap.m_to_wrap << TWrapper::closing_char;
}


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

inline void replace_all_not_of(fstr::fstr_ref in_out_str,
                               std::string_view in_allowed,
                               char in_replacement)
{
    bool table[256] = {false};

    for (unsigned char c : in_allowed)
        table[c] = true;

    for (auto& ch : in_out_str)
    {
        if (!table[static_cast<unsigned char>(ch)])
            ch = in_replacement;
    }
}

}

#endif // __fstringstream_h__
