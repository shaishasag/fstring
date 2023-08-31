#ifndef __fstring_h__
#define __fstring_h__

#include <stdexcept>
#include <cstring>
#include <cctype>
#include <string>
#include <string_view>
#include <type_traits>
#include <iterator>


namespace fixed
{
using size_type = std::size_t;
static constexpr size_type npos = size_type(-1);

template<class CharT>
class fstring_ref_base;

template<size_type TSize, class CharT>
class fstring_base
{
private:

    size_t m_capacity{TSize};
    size_t m_size{0};
    CharT m_str[TSize+1]{'\0'};

    constexpr void set_new_size(size_type new_size) noexcept
    {
        m_size = new_size;
        m_str[m_size] = '\0';
    }

    constexpr void __append__(const CharT in_char) noexcept
    {   // append a single char
        if (m_capacity > m_size)
        {
            m_str[m_size] = in_char;
            set_new_size(m_size+1);
        }
    }
    constexpr void __append__(const CharT* in_str)  noexcept
    {   // append null teminated char*
        if (nullptr == in_str) {
            return;
        }

        const CharT* endof = m_str + m_capacity;
        CharT* copy_to = m_str + m_size;
        const CharT* copy_from = in_str;
        while (copy_to < endof && '\0' != *copy_from)
        {
            *copy_to++ = *copy_from++;
        }
        set_new_size(copy_to - m_str);
    }
    constexpr void __append__(const CharT* in_str, const size_type in_size) noexcept
    {   // append char* by size
        if (nullptr == in_str || 0 == in_size) {
            return;
        }

        size_type num_chars_to_copy = std::min(in_size, vacancy());
        CharT* copy_to = m_str + m_size;
        memcpy(copy_to, in_str, num_chars_to_copy);
        set_new_size(m_size + num_chars_to_copy);
    }

public:
    using char_type = CharT;
    using traits_type = std::char_traits<CharT>;

    fstring_base() = default;

    template<class TFfirst, class... TRest>
    constexpr fstring_base(const TFfirst in_1, const TRest& ...in_rest) noexcept
    : fstring_base()
    {
        recursive_helper_to_variadic_constructor(in_1, in_rest...);
    }

    constexpr void recursive_helper_to_variadic_constructor()  noexcept {}

    template<class TFfirst, class... TRest>
    constexpr void recursive_helper_to_variadic_constructor(const TFfirst in_1, const TRest& ...in_rest) noexcept
    {
        append(in_1);
        recursive_helper_to_variadic_constructor(in_rest...);
    }

    constexpr operator std::string_view() const  noexcept
    {
        return std::string_view(c_str(), size());
    }
    constexpr std::string_view sv() const  noexcept
    {
        return std::string_view(c_str(), size());
    }

    fstring_base& operator=(const CharT in_char) noexcept
    {
        clear();
        __append__(in_char);
        return *this;
    }

    template <class TConverible, class = std::enable_if<std::is_convertible_v<TConverible, std::string_view> > >
    fstring_base& operator=(const TConverible& in_converti) noexcept
    {
        clear();
        std::string_view as_sv = std::string_view(in_converti);
        __append__(as_sv.data(), as_sv.size());
        return *this;
    }

    constexpr fstring_base& assign(std::string_view sv) noexcept
    {
        clear();
        __append__(sv.data(), sv.size());
        return *this;
    }

    constexpr CharT& at(const size_type pos)
    {
        if (pos >= size())
            throw std::out_of_range("index out of range");
        return m_str[pos];
    }
    constexpr CharT at(const size_type pos) const
    {
        if (pos >= size())
            throw std::out_of_range("index out of range");
        return m_str[pos];
    }
    constexpr CharT& operator[](const size_type pos)  noexcept      { return m_str[pos]; }
    constexpr CharT  operator[](const size_type pos) const noexcept { return m_str[pos]; }
    constexpr CharT& front()  noexcept       { return m_str[0]; }
    constexpr CharT  front() const  noexcept { return m_str[0]; }
    constexpr CharT& back()  noexcept        { return m_str[size()-1]; }
    constexpr CharT  back() const  noexcept   { return m_str[size()-1]; }

    constexpr CharT* begin() noexcept                { return m_str; }
    constexpr const CharT* begin() const noexcept    { return m_str; }
    constexpr const CharT* cbegin() const noexcept   { return begin(); }
    constexpr CharT* end() noexcept                  { return m_str+m_size; }
    constexpr const CharT* end() const noexcept      { return m_str+m_size; }
    constexpr const CharT* cend() const noexcept     { return end(); }
    constexpr CharT* rbegin() noexcept                { return m_str+(m_size-1); }
    constexpr const CharT* rbegin() const noexcept    { return m_str+(m_size-1); }
    constexpr const CharT* rcbegin() const noexcept   { return rbegin(); }
    constexpr CharT* rend() noexcept                  { return m_str-1; }
    constexpr const CharT* rend() const noexcept      { return m_str-1; }
    constexpr const CharT* rcend() const noexcept     { return rend(); }
    constexpr CharT* data() noexcept { return m_str; }
    constexpr const CharT* data() const noexcept { return m_str; }
    constexpr const CharT* c_str() const noexcept { return data(); }
    [[nodiscard]] constexpr bool empty() const noexcept {return 0 == size();}
    [[nodiscard]] constexpr size_type size() const noexcept {return m_size;}
    [[nodiscard]] constexpr size_type length() const noexcept {return size();}
    [[nodiscard]] constexpr size_type max_size() const noexcept {return m_capacity;}
    constexpr void reserve(size_type new_cap) = delete;
    [[nodiscard]] constexpr size_type capacity() const noexcept {return max_size();}
    constexpr void shrink_to_fit()  noexcept {} // will do nothing
    constexpr void clear() noexcept
    {
        set_new_size(0);
    }


#pragma warning( push )
#pragma warning( disable : 4789 )
    constexpr fstring_base& insert(size_type index, size_type count, CharT ch)
    {
        if (index > size()) {
            throw std::out_of_range("index out of range");
        }
        if (count > vacancy()) {
            throw std::length_error("too many chars to insert");
        }

        std::memmove(m_str+index+count, m_str+index, size()-index);
        memset(m_str+index, ch, count);
        set_new_size(m_size + count);

        return *this;
    }

    constexpr fstring_base& insert(size_type index, const std::string_view sv, size_type count)
    {
        if (index > size()) {
            throw std::out_of_range("index out of range");
        }
        if (count > vacancy()) {
            throw std::length_error("too many chars to insert");
        }

        memmove(m_str+index+count, m_str+index, size()-index);
        memmove(m_str+index, sv.data(), count);
        set_new_size(m_size + count);

        return *this;
    }

#pragma warning( pop )

    constexpr fstring_base& insert(size_type index, const std::string_view sv)
    {
        return insert(index, sv, sv.size());
    }
    constexpr fstring_base& erase(size_type index = 0, size_type count=npos)
    {
        if (index > size()) {
            throw std::out_of_range("index out of range");
        }

        if (count >= size() - index) {
            m_size = index;
        }
        else
        {
            size_type num_chars_to_remove = std::min(count, size() - index);
            std::memmove((void*)(m_str+index), (void*)(m_str+(index+num_chars_to_remove)), size() - index - count);
            m_size -= count;
        }
        *end() = '\0';

        return *this;
    }
    constexpr CharT* erase(const CharT* position)
    {
        size_type position_index = std::distance((const CharT*)m_str, position);
        erase(position_index, 1);
        return m_str+position_index;
    }
    constexpr CharT* erase(const CharT* first, const CharT* last)
    {
        size_type index = first - m_str;
        size_type count = last - first;
        erase(index, count);

        return m_str+index;
    }

    constexpr void push_back(const CharT in_char)
    {
        if (full())
            throw std::length_error("fstring is full");
        __append__(in_char);
    }

    constexpr void pop_back()  noexcept { resize(size() - 1); }

    constexpr void append(const CharT in_char)  noexcept
    {
        __append__(in_char);
    }
    constexpr void append(size_type count, const CharT in_char) noexcept
    {
        while (m_capacity > m_size)
        {
            m_str[m_size++] = in_char;
        }
        m_str[m_size] = '\0';
    }
    constexpr void append(const CharT* in_str)  noexcept
    {
        __append__(in_str);
    }
    constexpr void append(const CharT* in_str, const size_type in_size) noexcept
    {
        __append__(in_str, in_size);
    }
    constexpr void append(std::string_view sv) noexcept
    {
        __append__(sv.data(), sv.size());
    }
    
    constexpr fstring_base& operator+=(const CharT in_char) noexcept
    {
        __append__(in_char);
        return *this;
    }
    constexpr fstring_base& operator+=(const CharT* in_str)  noexcept
    {
        __append__(in_str);
        return *this;
    }
    constexpr fstring_base& operator+=(std::string_view sv) noexcept
    {
        __append__(sv.data(), sv.size());
        return *this;
    }

    bool operator==(std::string_view sv) const  noexcept
    {
        return 0 == sv.compare(std::string_view(*this));
    }
    bool operator<(std::string_view sv) const  noexcept
    {
        return std::string_view(*this) < sv;
    }

    // compare: use string_view.compare when available in c++20
    // untill then only compare(const std::string_view) is provided
    int compare(const std::string_view s) const noexcept
    {
        size_type lhs_sz = size();
        size_type rhs_sz = s.size();
        int result = traits_type::compare(data(), s.data(), std::min(lhs_sz, rhs_sz));
        if (result != 0)
            return result;
        if (lhs_sz < rhs_sz)
            return -1;
        if (lhs_sz > rhs_sz)
            return 1;
        return 0;
    }
    constexpr int icompare(std::string_view sv) noexcept
    {
        int retVal = 0;
        const CharT* lhs = c_str();
        const CharT* rhs = sv.data();
        size_t compare_size = std::min(size(), sv.size());
        while (compare_size > 0 && retVal==0)
        {
            retVal = std::toupper(*lhs++) - std::toupper(*rhs++);
            --compare_size;
        }

        if (retVal==0) {
            retVal = (int)(size() - sv.size());
        }

        return retVal;
    }

    // starts_with:  use string_view.starts_with
    // ends_with:  use string_view.ends_with
    // contains: use string_view.contains
    // replace: ToDo
    // substr: use string_view.substr
    // copy: use string_view.copy

    void resize(const size_type count, CharT ch='\0')  noexcept
    {
        const size_type new_size = std::min(capacity(), count);
        if (size() < new_size)
        {
            memset(m_str+size(), ch, new_size-size()+1);
        }
        set_new_size(new_size);
    }

    // swap does not make sense for fixed-size string, use std::exchange
    constexpr void swap(fstring_base& other) noexcept = delete;
    // find: use string_view.find
    // rfind: use string_view.rfind
    // find_first_of: use string_view.find_first_of
    // find_last_of: use string_view.find_last_of
    // find_first_not_of: use string_view.find_first_not_of
    // find_last_not_of: use string_view.find_last_not_of
    constexpr void remove_prefix( size_type n )  noexcept
    {
        const size_type new_size = size()-n;
        if (n < size())
        {
            std::memmove(m_str, c_str()+n, size()-n);
        }
        set_new_size(new_size);
    }

    constexpr void remove_suffix( size_type n )  noexcept
    {
        if (n == size())
        {
            clear();
        }
        else if (n < size())
        {
            resize(size()-n);
        }
    }

    //---
    // functions below will be part of std::string(_view)? interface, with C++20
    // so currently impemented here
    constexpr bool starts_with( std::string_view sv ) const noexcept
    {
        return std::string_view(c_str(), size()).substr(0, sv.size()) == sv;
    }
    constexpr bool starts_with( CharT ch ) const noexcept
    {
        return !empty() && front() == ch;
    }
    constexpr bool ends_with( std::string_view in_sv ) const noexcept
    {
        return size() >= in_sv.size() && sv().compare(size() - in_sv.size(), npos, in_sv) == 0;
    }
    constexpr bool ends_with( CharT ch ) const noexcept
    {
        return !empty() && back() == ch;
    }
    constexpr bool contains( std::string_view in_sv ) const noexcept
    {
        return sv().find(in_sv) != npos;
    }
    constexpr bool contains( CharT c ) const noexcept
    {
        return sv().find(c) != npos;
    }

    // functions below are not part of std::string(_view)? interface
    constexpr size_type vacancy() const  noexcept {return capacity() - size();}
    constexpr size_type full() const  noexcept {return size() == capacity();}

    void trim_front(const CharT* t = " \f\n\r\t\v") noexcept
    {
        size_type pos = sv().find_first_not_of(t);
        if (npos != pos)
        {
            remove_prefix(pos);
        }

    }
    void trim_back(const CharT* t = " \f\n\r\t\v") noexcept
    {
        size_type pos = sv().find_last_not_of(t);
        if (npos != pos)
        {
            remove_suffix(size() - pos - 1);
        }

    }
    void trim(const CharT* t = " \f\n\r\t\v") noexcept
    {
        trim_back(t);
        trim_front(t);
    }

    fstring_base& operator<<(std::string_view sv) noexcept
    {
        __append__(sv.data(), sv.size());
        return *this;
    }

    fstring_base& operator<<(const char c) noexcept
    {
        __append__(c);
        return *this;
    }
    template<typename TToPrintf>
    constexpr fstring_base& printf(const TToPrintf in_to_print, const char* printf_format=nullptr) noexcept
    {
        bool remove_zeros{false};
        if (nullptr == printf_format)
        {
            if constexpr (std::is_floating_point_v<TToPrintf>) {
                printf_format = "%lf";
                remove_zeros = true;
            }
            else if constexpr (std::is_integral_v<TToPrintf> && std::is_signed_v<TToPrintf>) {
                printf_format = "%li";
            }
            else if constexpr (std::is_integral_v<TToPrintf> && std::is_unsigned_v<TToPrintf>) {
                printf_format = "%lu";
            }
        }

        int num_chars = std::snprintf(end(), vacancy(), printf_format, in_to_print);
        if (vacancy() == (size_type)num_chars)
        {
            // this means there was not enough room for the number
            // but final '\0' was printed anyway so actualy there are num_chars-1 chars
            --num_chars;
        }

        if (remove_zeros && num_chars > 1)// when ouput_size==1 there are no extra '0's
        {
            const bool is_dot_found = (memchr(end(), '.', num_chars-1) != nullptr);
            if (is_dot_found)
            {
                while (*(end()+(num_chars-1)) == '0') {// remove trailing zeros - if any
                    --num_chars;
                }
                if (*(end()+(num_chars-1)) == '.') {// remove decimal point - if any
                    --num_chars;
                }
            }
        }

        set_new_size(size()+num_chars);

        return *this;
    }
};


template<class CharT>
class fstring_ref_base
{
private:
    fstring_base<0, CharT>& m_referee;

public:
    using char_type = CharT;
    using traits_type = std::char_traits<CharT>;

    fstring_ref_base() = delete;

    template<size_type TSize>
    constexpr fstring_ref_base(fstring_base<TSize, CharT>& in_gstr)  noexcept
        : m_referee((fstring_base<0, CharT>&)in_gstr) {}

    template<size_type TSize>
    constexpr fstring_ref_base(const fstring_base<TSize, CharT>& in_gstr) noexcept
        : m_referee((fstring_base<0, CharT>&)in_gstr) {}

    constexpr operator std::string_view() const  noexcept { return std::string_view(m_referee); }
    constexpr std::string_view sv() const  noexcept { return std::string_view(m_referee); }

    template <class _Tp, class = std::enable_if<std::is_convertible_v<_Tp, std::string_view> > >
    fstring_ref_base& operator=(const _Tp& __t) noexcept
    {
        m_referee = __t;
        return *this;
    }

    fstring_ref_base& operator=(const fstring_ref_base in_ref) noexcept
    {
        m_referee = in_ref;
        return *this;
    }

    fstring_ref_base assign(std::string_view sv) noexcept {
        m_referee = sv;;
        return *this;
    }
    constexpr CharT& at(const size_type pos)                { m_referee.at(pos); }
    constexpr CharT  at(const size_type pos) const          { m_referee.at(pos); }
    constexpr CharT& operator[](const size_type pos) noexcept        { return m_referee[pos]; }
    constexpr CharT  operator[](const size_type pos) const  noexcept { return m_referee[pos]; }
    constexpr CharT& front()  noexcept       { return front(); }
    constexpr CharT  front() const  noexcept { return front(); }
    constexpr CharT& back() noexcept         { return back(); }
    constexpr CharT  back() const noexcept   { return back(); }

    constexpr CharT* begin() noexcept                { return m_referee.begin(); }
    constexpr const CharT* begin() const noexcept    { return m_referee.begin(); }
    constexpr const CharT* cbegin() const noexcept   { return m_referee.xbegin(); }
    constexpr CharT* end() noexcept                  { return m_referee.end(); }
    constexpr const CharT* end() const noexcept      { return m_referee.end(); }
    constexpr const CharT* cend() const noexcept     { return m_referee.cend(); }
    constexpr CharT* rbegin() noexcept                { return m_referee.rbegin(); }
    constexpr const CharT* rbegin() const noexcept    { return m_referee.rbegin(); }
    constexpr const CharT* rcbegin() const noexcept   { return m_referee.rcbegin(); }
    constexpr CharT* rend() noexcept                  { return m_referee.rend(); }
    constexpr const CharT* rend() const noexcept      { return m_referee.rend(); }
    constexpr const CharT* rcend() const noexcept     { return m_referee.rcend(); }
    constexpr CharT* data() noexcept { return m_referee.data(); }
    constexpr const CharT* data() const noexcept { return m_referee.data(); }
    constexpr const CharT* c_str() const noexcept { return m_referee.c_str(); }
    [[nodiscard]] constexpr bool empty() const noexcept {return m_referee.empty();}
    [[nodiscard]] constexpr size_type size() const noexcept {return m_referee.size();}
    [[nodiscard]] constexpr size_type length() const noexcept {return m_referee.size();}
    [[nodiscard]] constexpr size_type max_size() const noexcept {return m_referee.max_size();}
    constexpr void reserve(size_type new_cap) = delete;
    [[nodiscard]] constexpr size_type capacity() const noexcept {return m_referee.max_size();}
    constexpr void shrink_to_fit()  noexcept {m_referee.shrink_to_fit();} // will do nothing
    constexpr void clear() noexcept {m_referee.clear();}
    constexpr fstring_ref_base& insert(size_type index, size_type count, CharT ch)
    {
        m_referee.insert(index, count, ch);
        return *this;
    }
    constexpr fstring_ref_base& insert(size_type index, const std::string_view sv, size_type count)
    {
        m_referee.insert(index, sv, count);
        return *this;
    }
    constexpr fstring_ref_base& insert(size_type index, const std::string_view sv)
    {
        m_referee.insert(index, sv);
        return *this;
    }
    constexpr fstring_ref_base& erase(size_type index = 0, size_type count=npos)
    {
        return m_referee.erase(index, count);
    }
    constexpr CharT* erase(const CharT* position)
    {
        return m_referee.erase(position);
    }
    constexpr CharT* erase(const CharT* first, const CharT* last)
    {
        return m_referee.erase(first, last);
    }
    constexpr void push_back(const CharT in_char)  {return m_referee.push_back(in_char);}
    constexpr void pop_back() noexcept {return m_referee.pop_back();}
    constexpr void append(size_type count, const CharT in_char) noexcept {return m_referee.append(count, in_char);}
    constexpr void append(const CharT* in_str)  noexcept {return m_referee.append(in_str);}
    constexpr void append(const CharT* in_str, const size_type in_size) noexcept {return m_referee.append(in_str, in_size);}
    constexpr void append(std::string_view sv) noexcept {return m_referee.append(sv);}
    constexpr fstring_ref_base& operator+=(const CharT in_char) noexcept
    {
        m_referee += in_char;
        return *this;
    }
    constexpr fstring_ref_base& operator+=(const CharT* in_str)  noexcept
    {
        m_referee += in_str;
        return *this;
    }
    constexpr fstring_ref_base& operator+=(std::string_view sv) noexcept
    {
        m_referee += sv;
        return *this;
    }
    constexpr int icompare(std::string_view sv) noexcept {return m_referee.icompare(sv);}
    void resize(const size_type count, CharT ch='\0') noexcept {return m_referee.resize(count, ch);}
    // starts_with:  use string_view.starts_with
    // ends_with:  use string_view.ends_with
    // contains: use string_view.contains
    // replace: ToDo
    // substr: use string_view.substr
    // copy: use string_view.copy
    // swap does not make sence for fixed-size string, use std::exchange
    constexpr void swap(fstring_ref_base& other) noexcept = delete;
    // find: use string_view.find
    // rfind: use string_view.rfind
    // find_first_of: use string_view.find_first_of
    // find_last_of: use string_view.find_last_of
    // find_first_not_of: use string_view.find_first_not_of
    // find_last_not_of: use string_view.find_last_not_of

    //---
    constexpr size_type vacancy() const noexcept{ return m_referee.vacancy(); }
    constexpr size_type full() const noexcept { return m_referee.full(); }
    void trim_front(const CharT* t = " \f\n\r\t\v") noexcept { return m_referee.trim_front(t); }
    void trim_back(const CharT* t = " \f\n\r\t\v") noexcept { return m_referee.trim_back(t); }
    void trim(const CharT* t = " \f\n\r\t\v") noexcept { return m_referee.trim(t); }

    fstring_ref_base& operator<<(std::string_view sv) noexcept
    {
        m_referee << sv;
        return *this;
    }

    fstring_ref_base& operator<<(const char c) noexcept
    {
        m_referee << c;
        return *this;
    }
    template<typename TToPrintf>
    constexpr fstring_ref_base& printf(const TToPrintf in_to_print, const char* printf_format=nullptr) noexcept
    {
        m_referee.printf(in_to_print, printf_format);
    }

};

typedef  fstring_ref_base<char> fstring_ref;
typedef  fstring_base<7,  char> fstring7;
typedef  fstring_base<15, char> fstring15;
typedef  fstring_base<31, char> fstring31;
typedef  fstring_base<63, char> fstring63;
typedef  fstring_base<127,char> fstring127;
typedef  fstring_base<255,char> fstring255;
typedef  fstring_base<511,char> fstring511;
typedef  fstring_base<1023, char> fstring1023;

}
#endif // __fstring_h__
