#ifndef fstring_h
#define fstring_h

#include <string>
#include <string_view>

namespace fixed
{
using size_type = std::size_t;
static constexpr size_type npos = size_type(-1);

template<class TActual, class CharT>
class meta_fstring
{
public:


    constexpr size_type size() const {return ActualPtr()->m_insides.m_size;}
    constexpr size_type length() const {return size();}
    constexpr size_type capacity() const {return ActualPtr()->m_insides.m_capacity;}
    constexpr size_type max_size() const {return capacity();}
    constexpr size_type full() const {return size() == capacity();}
    constexpr size_type empty() const {return 0 == size();}
    constexpr const CharT* c_str() const {return ActualPtr()->m_insides.m_str; }
    constexpr const CharT* data() const noexcept { return c_str(); }

    void reserve() = delete;
    void shrink_to_fit() = delete;

    void clear()
    {
        ActualPtr()->m_insides.m_str[0] = '\0';
        ActualPtr()->m_insides.m_size = 0;
    }

    void operator+=(const CharT in_char) {ActualPtr()->__append__(in_char);}
    void operator+=(const CharT* in_str) {ActualPtr()->__append__(in_str);}

    void operator=(const CharT in_char)
    {
        clear();
        ActualPtr()->__append__(in_char);
    }
    void operator=(const CharT* in_str)
    {
        clear();
        ActualPtr()->__append__(in_str);
    }

    constexpr CharT& operator[](const size_type pos)       { return peek()[pos]; }
    constexpr CharT  operator[](const size_type pos) const { return c_str()[pos]; }

    constexpr CharT* begin() noexcept                { return peek(); }
    constexpr const CharT* begin() const noexcept    { return c_str(); }
    constexpr const CharT* cbegin() const noexcept   { return c_str(); }
    constexpr CharT* end() noexcept                  { return peek()+size(); }
    constexpr const CharT* end() const noexcept      { return c_str()+size(); }
    constexpr const CharT* cend() const noexcept     { return c_str()+size(); }

    constexpr CharT& at(const size_type pos)
    {
        if (pos >= size())
            throw std::out_of_range("index out of range");
        return peek()[pos];
    }
    constexpr CharT at(const size_type pos) const
    {
        if (pos >= size())
            throw std::out_of_range("index out of range");
        return c_str()[pos];
    }
    constexpr CharT& front() { return peek()[0]; }
    constexpr CharT& back()  { return peek()[size()-1]; }
    constexpr CharT  front() const { return c_str()[0]; }
    constexpr CharT  back() const  { return c_str()[size()-1]; }

    constexpr void push_back(const CharT in_char)
    {
        ActualPtr()->__append__(in_char);
    }

    constexpr void pop_back()
    {
        resize(size() - 1);
    }

    void resize(const size_type count)
    {
        if (size() >= count)
        {
            ActualPtr()->m_insides.m_size = count;
            ActualPtr()->m_insides.m_str[count] = '\0';
        }
        else
        {
            const size_type new_size = std::min(capacity(), count);
            memset(ActualPtr()->m_insides.m_str+size(), '\0', new_size-size()+1);
            ActualPtr()->m_insides.m_size = new_size;
        }
    }

    constexpr void remove_prefix( size_type n )
    {
        if (n == size())
        {
            clear();
        }
        else if (n < size())
        {
            const size_type new_size = size()-n;
            std::memmove(peek(), c_str()+n, size()-n);
            ActualPtr()->m_insides.m_size = new_size;
            ActualPtr()->m_insides.m_str[new_size] = '\0';
        }
    }
    constexpr void remove_suffix( size_type n )
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

    constexpr size_type copy( CharT* dest, size_type count, size_type pos = 0 ) const
    {
        return std::string_view(c_str(), size()).copy(dest, count, pos);
    }

    //constexpr basic_string_view substr( size_type pos = 0, size_type count = npos ) const;


    constexpr int compare( std::string_view v ) const noexcept
    {
        return std::string_view(c_str(), size()).compare(v);
    }
    constexpr int compare( size_type pos1, size_type count1, std::string_view v ) const
    {
        return std::string_view(c_str(), size()).compare(pos1, count1, v);
    }
    constexpr int compare( size_type pos1, size_type count1, std::string_view v,
                           size_type pos2, size_type count2 ) const
    {
        return std::string_view(c_str(), size()).compare(pos1, count1, v, pos2, count2);
    }
    constexpr int compare( const CharT* s ) const
    {
        return std::string_view(c_str(), size()).compare(s);
    }
    constexpr int compare( size_type pos1, size_type count1, const CharT* s ) const
    {
        return std::string_view(c_str(), size()).compare(pos1, count1, s);
    }
    constexpr int compare( size_type pos1, size_type count1,
                           const CharT* s, size_type count2 ) const
    {
        return std::string_view(c_str(), size()).compare(pos1, count1, s, count2);
    }


    constexpr bool starts_with( std::string_view sv ) const noexcept
    {
        return std::string_view(c_str(), size()).substr(0, sv.size()) == sv;
    }
    constexpr bool starts_with( CharT ch ) const noexcept
    {
        return !empty() && front() == ch;
    }
    constexpr bool starts_with( const CharT* s ) const
    {
        return starts_with(std::string_view(s));
    }

    constexpr bool ends_with( std::string_view sv ) const noexcept
    {
        return size() >= sv.size() && compare(size() - sv.size(), npos, sv) == 0;
    }
    constexpr bool ends_with( CharT ch ) const noexcept
    {
        return !empty() && back() == ch;
    }
    constexpr bool ends_with( const CharT* s ) const
    {
        return ends_with(std::string_view(s));
    }

    constexpr bool contains( std::string_view sv ) const noexcept
    {
        return find(sv) != npos;
    }
    constexpr bool contains( CharT c ) const noexcept
    {
        return find(c) != npos;
    }
    constexpr bool contains( const CharT* s ) const
    {
        return find(s) != npos;
    }

    constexpr size_type find(const std::string_view v, const size_type pos=0) const noexcept
    {
        return std::string_view(c_str(), size()).find(v, pos);
    }
    constexpr size_type find(const CharT ch, const size_type pos=0) const noexcept
    {
        return std::string_view(c_str(), size()).find(ch, pos);
    }
    constexpr size_type find(const CharT* s, const size_type pos, const size_type count) const
    {
        return std::string_view(c_str(), size()).find(s, pos, count);
    }
    constexpr size_type find(const CharT* s, const size_type pos=0) const
    {
        return std::string_view(c_str(), size()).find(s, pos);
    }

    constexpr size_type rfind(std::string_view v, size_type pos = npos) const noexcept
    {
        return std::string_view(c_str(), size()).rfind(v, pos);
    }
    constexpr size_type rfind( CharT ch, size_type pos = npos ) const noexcept
    {
        return std::string_view(c_str(), size()).rfind(ch, pos);
    }
    constexpr size_type rfind( const CharT* s, size_type pos, size_type count ) const
    {
        return std::string_view(c_str(), size()).rfind(s, pos, count);
    }
    constexpr size_type rfind( const CharT* s, size_type pos = npos ) const
    {
        return std::string_view(c_str(), size()).rfind(s, pos);
    }

    constexpr size_type find_first_of( std::string_view v, size_type pos = 0 ) const noexcept
    {
        return std::string_view(c_str(), size()).find_first_of(v, pos);
    }
    constexpr size_type find_first_of( CharT ch, size_type pos = 0 ) const noexcept
    {
        return std::string_view(c_str(), size()).find_first_of(ch, pos);
    }
    constexpr size_type find_first_of( const CharT* s, size_type pos, size_type count ) const
    {
        return std::string_view(c_str(), size()).find_first_of(s, pos, count);
    }
    constexpr size_type find_first_of( const CharT* s, size_type pos = 0 ) const
    {
        return std::string_view(c_str(), size()).find_first_of(s, pos);
    }

    constexpr size_type find_last_of( std::string_view v, size_type pos = npos ) const noexcept
    {
        return std::string_view(c_str(), size()).find_last_of(v, pos);
    }
    constexpr size_type find_last_of( CharT ch, size_type pos = npos ) const noexcept
    {
        return std::string_view(c_str(), size()).find_last_of(ch, pos);
    }
    constexpr size_type find_last_of( const CharT* s, size_type pos, size_type count ) const
    {
        return std::string_view(c_str(), size()).find_last_of(s, pos, count);
    }
    constexpr size_type find_last_of( const CharT* s, size_type pos = npos ) const
    {
        return std::string_view(c_str(), size()).find_last_of(s, pos);
    }

    constexpr size_type find_first_not_of( std::string_view v, size_type pos = 0 ) const noexcept
    {
        return std::string_view(c_str(), size()).find_first_not_of(v, pos);
    }
    constexpr size_type find_first_not_of( CharT ch, size_type pos = 0 ) const noexcept
    {
        return std::string_view(c_str(), size()).find_first_not_of(ch, pos);
    }
    constexpr size_type find_first_not_of( const CharT* s, size_type pos, size_type count ) const
    {
        return std::string_view(c_str(), size()).find_first_not_of(s, pos, count);
    }
    constexpr size_type find_first_not_of( const CharT* s, size_type pos = 0 ) const
    {
        return std::string_view(c_str(), size()).find_first_not_of(s, pos);
    }

    constexpr size_type find_last_not_of( std::string_view v, size_type pos = npos ) const noexcept
    {
        return std::string_view(c_str(), size()).find_last_not_of(v, pos);
    }
    constexpr size_type find_last_not_of( CharT ch, size_type pos = npos ) const noexcept
    {
        return std::string_view(c_str(), size()).find_last_not_of(ch, pos);
    }
    constexpr size_type find_last_not_of( const CharT* s, size_type pos, size_type count ) const
    {
        return std::string_view(c_str(), size()).find_last_not_of(s, pos, count);
    }
    constexpr size_type find_last_not_of( const CharT* s, size_type pos = npos ) const
    {
        return std::string_view(c_str(), size()).find_last_not_of(s, pos);
    }

    void trim_front(const CharT* t = " \f\n\r\t\v")
    {
        size_type pos = find_first_not_of(t);
        if (npos != pos)
        {
            remove_prefix(pos);
        }

    }
    void trim_back(const CharT* t = " \f\n\r\t\v")
    {
        size_type pos = find_last_not_of(t);
        if (npos != pos)
        {
            remove_suffix(size() - pos - 1);
        }

    }
    void trim(const CharT* t = " \f\n\r\t\v")
    {
        trim_back(t);
        trim_front(t);
    }

protected:

    constexpr const TActual* ActualPtr() const { return static_cast<const TActual*>(this); }
    constexpr TActual* ActualPtr() { return static_cast<TActual*>(this); }

    CharT* peek() {return ActualPtr()->m_insides.m_str; }

    constexpr void __append__(const CharT* in_str)
    {
        if (nullptr == in_str) {
            this->clear();
            return;
        }

        auto p = ActualPtr();

        const CharT* endof = p->m_insides.m_str + p->capacity();
        CharT* copy_to = p->m_insides.m_str + p->m_insides.m_size;
        const CharT* copy_from = in_str;
        while (copy_to < endof && '\0' != *copy_from)
        {
            *copy_to++ = *copy_from++;
        }
        *copy_to = '\0';
        p->m_insides.m_size = copy_to - p->m_insides.m_str;
    }
    constexpr void __append__(const CharT in_char)
    {
        auto p = ActualPtr();
        p->__append__(&in_char, 1);
    }
    constexpr void __append__(const CharT* in_str, const size_type in_size)
    {
        if (0 == in_size) {
            return;
        }

        auto p = ActualPtr();
        size_type num_chars_to_copy = std::min(in_size, p->capacity() - p->size());
        CharT* copy_to = p->m_insides.m_str + p->m_insides.m_size;
        memcpy(copy_to, in_str, num_chars_to_copy);
        *(copy_to+num_chars_to_copy) = '\0';
        p->m_insides.m_size += num_chars_to_copy;
    }
};

template<class CharT> class fstring_ref_base;

template<size_type TSize, class CharT>
class fstring_base : public meta_fstring<fstring_base<TSize, CharT>, CharT>
{
    friend class meta_fstring<fstring_base<TSize, CharT>, CharT>;
    friend class fstring_ref_base<CharT>;
protected:
    struct insides
    {
        size_t m_capacity{TSize};
        size_t m_size{0};
        CharT m_str[TSize+1]{'\0'};
    } m_insides;

public:

    constexpr fstring_base(const CharT in_char)
    : fstring_base()
    {
        meta_fstring<fstring_base<TSize, CharT>, CharT>::__append__(in_char);
    }

    constexpr fstring_base(const CharT* in_str)
    : fstring_base()
    {
        meta_fstring<fstring_base<TSize, CharT>, CharT>::__append__(in_str);
    }

    constexpr fstring_base(const CharT* in_str, const size_t in_size)
    : fstring_base()
    {
        meta_fstring<fstring_base<TSize, CharT>, CharT>::__append__(in_str, in_size);
    }

    constexpr fstring_base()
    : m_insides({TSize, 0})
    {
        m_insides.m_str[0] = '\0';
    }

    template<size_t TOtherSize>
    constexpr fstring_base(const fstring_base<TOtherSize, CharT>& in_my_str)
    : fstring_base(in_my_str.c_str(), in_my_str.size())
    {}

    template<size_t TOtherSize>
    constexpr fstring_base(fstring_base<TOtherSize, CharT>&& in_my_str)
    : fstring_base(in_my_str.c_str(), in_my_str.size())
    {}

    constexpr fstring_base(const std::string& in_std_str)
    : fstring_base(in_std_str.c_str(), in_std_str.size())
    {}

    constexpr fstring_base(const std::string_view in_std_strv)
    : fstring_base(in_std_strv.data(), in_std_strv.size())
    {}

    template<class TFfirst, class... TRest>
    constexpr fstring_base(const TFfirst in_1, const TRest& ...in_rest)
    {
        meta_fstring<fstring_base<TSize, CharT>, CharT>::__append__(in_1);
        recursive_helper_to_variadic_constructor(in_rest...);
    }

    constexpr void recursive_helper_to_variadic_constructor() {}

    template<class TFfirst, class... TRest>
    constexpr void recursive_helper_to_variadic_constructor(const TFfirst in_1, const TRest& ...in_rest)
    {
        meta_fstring<fstring_base<TSize, CharT>, CharT>::__append__(in_1);
        recursive_helper_to_variadic_constructor(in_rest...);
    }

    template<size_t TOtherSize>
    constexpr fstring_base& operator=(const fstring_base<TOtherSize, CharT>& in_fixed)
    {
        this->clear();
        __append__(in_fixed.c_str(), in_fixed.size());
        return *this;
    }

    template<size_t TOtherSize>
    constexpr fstring_base& operator=(fstring_base<TOtherSize, CharT>&& in_fixed)
    {
        this->clear();
        __append__(in_fixed.c_str(), in_fixed.size());
        return *this;
    }

    constexpr operator std::string_view()
    {
        return std::string_view(this->c_str(), this->size());
    }
    operator std::string()
    {
        return std::string(this->c_str(), this->size());
    }

private:
};

template<class CharT>
class fstring_ref_base : public meta_fstring<fstring_ref_base<CharT>, CharT>
{
public:
    struct insides
    {
        size_t m_capacity;
        size_t m_size;
        CharT m_str[];
    }& m_insides;

    fstring_ref_base() = delete;

    constexpr fstring_ref_base(const fstring_ref_base& in_fref)
    : fstring_ref_base(in_fref.m_insides)
    {}

    template<size_t TSize>
    fstring_ref_base(fstring_base<TSize, CharT>& in_fixed)
    : fstring_ref_base((insides&)in_fixed.m_insides)
    {}

    template<size_t TSize>
    constexpr fstring_ref_base(const fstring_base<TSize, CharT>& in_fixed)
    : fstring_ref_base((insides&)in_fixed.m_insides)
    {}

    constexpr operator std::string_view()
    {
        return std::string_view(this->c_str(), this->size());
    }

    operator std::string()
    {
        return std::string(this->c_str(), this->size());
    }

private:
    constexpr fstring_ref_base(insides& in_insides)
    : m_insides(in_insides)
    {}

};


typedef  fstring_ref_base<char> fstring_ref;
typedef  fstring_base<7,  char> fstring7;
typedef  fstring_base<15, char> fstring15;
typedef  fstring_base<31, char> fstring31;
typedef  fstring_base<63, char> fstring63;
typedef  fstring_base<127,char> fstring127;

}

template<class CharT, class Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, fixed::fstring_ref v)
{
    os << std::string_view(v);
    return os;
}

inline bool operator==(fixed::fstring_ref lhs, fixed::fstring_ref rhs) noexcept
{
    return 0 == lhs.compare(rhs);
}


#endif /* fstring_h */
