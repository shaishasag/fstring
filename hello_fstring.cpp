#include <stdlib.h>
#include <iostream>
#include <cassert>

#include "fstring.h"
#include "fstringstream.h"

template<typename TStr>
struct fixed_or_std_str_ref
{
    TStr m_string_ref;
    
    void reserve( size_t new_cap )
    {
        if constexpr (std::is_same_v<std::string, std::decay_t<TStr>>)
        {
            m_string_ref.reserve(new_cap);
        }
        else if constexpr (std::is_same_v<fstr::fstr_ref, TStr>)
        {
            assert(new_cap <= m_string_ref.capacity());
        }
    }
    size_t size() const
    {
        return m_string_ref.size();
    }
    size_t capacity() const
    {
        return m_string_ref.capacity();
    }
    size_t max_size() const
    {
        return m_string_ref.max_size();
    }
    const char* c_str() const
    {
        return m_string_ref.c_str();
    }
    
    fixed_or_std_str_ref& operator=(std::string_view in_sv)
    {
        m_string_ref = in_sv;
        return *this;
    }
    
    fixed_or_std_str_ref& operator+=(std::string_view in_sv)
    {
        m_string_ref += in_sv;
        return *this;
    }
    
    char& operator[]( size_t pos )
    {
        return m_string_ref[pos];
    }
    
    const char& operator[]( size_t pos ) const
    {
        return m_string_ref[pos];
    }
    
    void resize( size_t count )
    {
        m_string_ref.resize(count);
    }
    
    char* data()
    {
        return m_string_ref.data();
    }
    
    constexpr const char*const data() const
    {
        return m_string_ref.data();
    }

    constexpr operator std::string_view() const  noexcept
    {
        return std::string_view(c_str(), size());
    }
    
    constexpr void clear() noexcept {m_string_ref.clear();}
    
    constexpr fixed_or_std_str_ref& insert(size_t index, size_t count, char ch)
    {
        m_string_ref.insert(index, count, ch);
        return *this;
    }
    constexpr fixed_or_std_str_ref& insert(size_t index, const std::string_view sv, size_t count)
    {
        m_string_ref.insert(index, sv, count);
        return *this;
    }
    constexpr fixed_or_std_str_ref& insert(size_t index, const std::string_view sv)
    {
        m_string_ref.insert(index, sv);
        return *this;
    }
    constexpr fixed_or_std_str_ref& replace(size_t pos, size_t count,
                                    const std::string_view replacement_str)
    {
        m_string_ref.replace(pos, count, replacement_str);
        return *this;
    }
    constexpr fixed_or_std_str_ref& replace(size_t pos, const std::string_view replacement_str)
    {
        m_string_ref.replace(pos, replacement_str);
        return *this;
    }
};

template<typename TStr>
static void ukalili(const char* name, fixed_or_std_str_ref<TStr> the_ref)
{
    the_ref = "UKALILI";
    the_ref += "!";
    std::cout << name << ":\n";
    std::cout << "    '" << std::string_view(the_ref) << "'\n";
    std::cout << "    size: " << the_ref.size() << " chars\n";
    std::cout << "    capacity: " << the_ref.capacity() << " chars\n";
    std::cout << "    max_size: " << the_ref.max_size() << " chars\n";
    std::cout << "    1st char: " << the_ref[0] << "\n";
    std::cout << "    last char: " << the_ref[the_ref.size()-1] << "\n";
    the_ref.resize(3);
    std::cout << "    after resize(3): " << the_ref.data() << "\n";
    the_ref.reserve(30);
    std::cout << "    after reserve(30), capacity: " << the_ref.capacity() << "\n";
}

static constexpr fstr::fstr127 will_it_constexpr()
{
    constexpr fstr::fstr31 f0;
    constexpr fstr::fstr31 f1('X');
    constexpr fstr::fstr31 f2("Y");
    constexpr fstr::fstr31 f3("Z"sv);
    constexpr fstr::fstr31 b0(false);
    constexpr fstr::fstr31 b1(true);
    fstr::fstr31 f4(1); // number conversions are not constexpr yet
    fstr::fstr31 f5(2.3);

    fstr::fstr127 retVal(b0, f0, f1, b1, f2, f3, f4, f5);
    return retVal;
}

int main(int argc, char** argv)
{
    std::cout << "sizeof(fstr::fstr_base<0, char>) = " << sizeof(fstr::fstring_base<0, char>)  << std::endl;
    std::cout << "sizeof(fstr::fstr15) = " << sizeof(fstr::fstr15)  << std::endl;
    std::cout << "sizeof(fstr::fstr31) = " << sizeof(fstr::fstr31)  << std::endl;
    std::cout << "sizeof(fstr::fstr63) = " << sizeof(fstr::fstr63)  << std::endl;
    std::cout << "sizeof(fstr::fstr_base_ref) = " << sizeof(fstr::fstr_ref)  << std::endl;

    constexpr fstr::fstr31 fstr("Hello fstring");
    std::cout << std::string_view(fstr) << std::endl;
    
    {
        fstr::fstr31 original("ukalili");
        fixed_or_std_str_ref<fstr::fstr_ref> the_ref{original};
        ukalili("fixed_ref", the_ref);
    }
    {
        std::string original("ukalili");
        fixed_or_std_str_ref<std::string&> the_ref{original};
        ukalili("std_ref", the_ref);
    }
    {
        std::string original("ukalili");
        fixed_or_std_str_ref<std::string> the_ref{original};
        ukalili("std_conc", the_ref);
    }

    auto sum_of_all_constexpr = will_it_constexpr();
    std::cout << sum_of_all_constexpr.sv() << std::endl;
    
    return 0;
}
