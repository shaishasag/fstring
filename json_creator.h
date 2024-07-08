#ifndef __json_creator_h__
#define __json_creator_h__

#include <string.h>
#include <string>
#include <string_view>
#include <charconv>

#include "fstring.h"
#include "fstringstream.h"

/* Copy to include
#include "json_creator.h"
*/


#ifndef DllExport
   #define DllExport
#endif


namespace fixed
{

#ifndef OBJECT_WHITESPACE_AFTER_COMMA
    #define OBJECT_WHITESPACE_AFTER_COMMA " "
#endif
constexpr std::string_view ___object_whitespace_after_comma{OBJECT_WHITESPACE_AFTER_COMMA};

#ifndef ARRAY_WHITESPACE_AFTER_COMMA
    #define ARRAY_WHITESPACE_AFTER_COMMA " "
#endif
constexpr std::string_view ___array_whitespace_after_comma{ARRAY_WHITESPACE_AFTER_COMMA};

namespace internal
{
    constexpr fstring7 _TRUE{"true"};
    constexpr fstring7 _FALSE{"false"};
    constexpr fstring7 _NULL{"false"};
    constexpr fstring7 _COMMA{","};
    constexpr fstring7 _KEY_VAL_SEP{R"|(": )|"};

    template <typename TValue>
    inline void write_value(const TValue in_value, fstring_ref in_json_str)
    {
        if constexpr (std::is_same_v<bool, TValue>)
        {
            in_json_str += in_value ? _TRUE : _FALSE;
        }
        else if constexpr (std::is_same_v<char, TValue>)
        {
            in_json_str += '"';
            in_json_str += in_value;
            in_json_str += '"';
        }
        else if constexpr (std::is_same_v<std::byte, TValue>)
        {
            in_json_str.printf(in_value);
        }
        else if constexpr (std::is_integral_v<TValue>)
        {
            in_json_str.printf(in_value);
        }
        else if constexpr (std::is_floating_point_v<TValue>)
        {
            in_json_str.printf(in_value);
        }
        else if constexpr (std::is_null_pointer_v<TValue>)
        {
            in_json_str += _NULL;
        }
        else if constexpr (std::is_convertible_v<TValue, std::string_view>)
        {
            in_json_str += '"';
            in_json_str += std::string_view(in_value);
            in_json_str += '"';
        }
        else
        {
            // if you got a compilation error here, it means
            // append_value was call on type that is string/number/boolean/null
            // to fix, convert to string before calling append_value
            in_json_str += '"';
            in_json_str += in_value;
            in_json_str += '"';
        }
    }
}


class DllExport base_json_creator
{
private:
    static const size_t t_max_levels{15};

protected:

    // for use by sub-classes that provide their own fstring member
    class PreventAmbiguityOnConstructorCalls{}; // dummy class to help compiler to mark construction from inheriting classes json_object_creator, json_array_creator

    template<size_t STRING_CAPACITY>
    base_json_creator(fstring_base<STRING_CAPACITY, char>& in_fstr_to_refer_to, PreventAmbiguityOnConstructorCalls) noexcept
    : m_json_fstring_ref(in_fstr_to_refer_to)
    {}

    base_json_creator(fstring_ref the_str, size_t start_level)  noexcept
    : m_json_fstring_ref(the_str)
    , m_level(start_level)
    {}

    fstring_ref m_json_fstring_ref;

    size_t m_num_subs{0};
    size_t m_level{0};

    std::string_view save_end();
    void restore_end(std::string_view in_end);

    class save_restore_end
    {
    public:
        save_restore_end(base_json_creator& to_save) noexcept;
        ~save_restore_end();

    private:
        base_json_creator&    m_creator_to_save;
        std::string_view m_saved_end_chars;

        char m_save_buf[t_max_levels+1];
    };

public:

    [[nodiscard]] size_t size() const { return m_json_fstring_ref.size(); }
    [[nodiscard]] size_t capacity() const { return m_json_fstring_ref.capacity(); }
    [[nodiscard]] size_t max_size() const { return m_json_fstring_ref.max_size(); }
    [[nodiscard]] const char* c_str() const { return m_json_fstring_ref.c_str(); }
    [[nodiscard]] operator std::string_view() const { return m_json_fstring_ref;}
};


class sub_array_json_creator;

class DllExport sub_object_json_creator : public base_json_creator
{
    friend class sub_array_json_creator;
    template<size_t> friend class object_json_creator;

protected:
    constexpr static inline std::string_view empty_json_object{"{}"};

    void prepare_for_additional_value(const std::string_view in_key);

    // this constructor should only be called from json_object_creator::append_object or json_array_creator::append_object
    sub_object_json_creator(fstring_ref the_str, size_t start_level) noexcept
    : base_json_creator(the_str, start_level)
    {
        m_json_fstring_ref += empty_json_object;
    }

    // this constructor should only be called from json_object_creator::json_object_creator
    // the purpose of this constructor is to avoid using m_json_fstring_ref before it was intialized
    // by json_object_creator
    // for use by sub-classes that provide their own fstring member
    template<size_t STRING_CAPACITY>
    sub_object_json_creator(fstring_base<STRING_CAPACITY, char>& in_fstr_to_refer_to,
                       PreventAmbiguityOnConstructorCalls in_unambig) noexcept
    : base_json_creator(in_fstr_to_refer_to, in_unambig)
    {}

public:

    [[nodiscard]] sub_object_json_creator append_object(std::string_view in_key);
    [[nodiscard]] sub_array_json_creator append_array(std::string_view in_key);

    // add a value that is already formated as json to the end of the object
    void append_json_str(const std::string_view in_key, const std::string_view in_value);

    // add a value that is already formated as json to the begening of the object
    // Warning: less efficient than append_json_str!
    void prepend_json_str(const std::string_view in_key, const std::string_view in_value);

    template <typename TValue>
    void append_value(const std::string_view in_key, const TValue& in_value)
    {
        base_json_creator::save_restore_end sv(*this);
        prepare_for_additional_value(in_key);
        internal::write_value(in_value, m_json_fstring_ref);
    }

    void append_value(const std::string_view in_key, const char* in_value)
    {
        std::string_view as_sv(in_value);
        append_value<std::string_view>(in_key, as_sv);
    }

    template<typename TContainer>
    void extend(const TContainer& in_val_key_container)
    {
        for (auto& [name, value] : in_val_key_container)
        {
            append_value(std::string_view(name), value);
        }
    }

    void append_values_from(const sub_object_json_creator& in_to_merge_from);
    void prepend_values_from(const sub_object_json_creator& in_to_merge_from);

    [[nodiscard]] bool empty() const { return m_json_fstring_ref[1] == empty_json_object[1]; }
    void clear() { m_json_fstring_ref = empty_json_object; m_num_subs = 0; }
};



class DllExport sub_array_json_creator : public base_json_creator
{
    friend class sub_object_json_creator;
    template<size_t> friend class  array_json_creator;

protected:
    constexpr static inline std::string_view empty_json_array{"[]"};

    void prepare_for_additional_value();

    sub_array_json_creator(fstring_ref the_str, size_t start_level) noexcept
    : base_json_creator(the_str, start_level)
    {
        m_json_fstring_ref += empty_json_array;
    }

    // this constructor should only be called from json_object_creator::json_object_creator
    // the purpose of this constructor is to avoid using m_json_fstring_ref before it was intialized
    // by json_object_creator
    // for use by sub-classes that provide their own fstring member
    template<size_t STRING_CAPACITY>
    sub_array_json_creator(fstring_base<STRING_CAPACITY, char>& in_fstr_to_refer_to,
                       PreventAmbiguityOnConstructorCalls in_unambig) noexcept
    : base_json_creator(in_fstr_to_refer_to, in_unambig)
    {}

public:

    [[nodiscard]] sub_array_json_creator append_array();
    [[nodiscard]] sub_object_json_creator append_object();

    // add a value that is already formated as json
    void append_json_str(const std::string_view in_value);

    // add a value that is already formated as json to the begening of the array
    // Warning: less efficient than append_json_str!
    void prepend_json_str(const std::string_view in_value);

    void append_value() {}
    void append_value(const char* in_value);

    template <typename TValue>
    void append_value(const TValue& in_value)
    {
        typename sub_array_json_creator::save_restore_end sv(*this);
        prepare_for_additional_value();
        internal::write_value(in_value, m_json_fstring_ref);
    }

    template<typename TValue, typename... Args>
    void append_value(const TValue& in_value, Args&&... args)
    {
        append_value(in_value);
        append_value(std::forward<Args>(args)...);
    }

    template<typename TContainer>
    void extend(const TContainer& in_values_container)
    {
        for (const auto& value : in_values_container)
        {
            append_value(value);
        }
    }

    void append_values_from(const sub_array_json_creator& in_to_merge_from);
    void prepend_values_from(const sub_array_json_creator& in_to_merge_from);

    [[nodiscard]] bool empty() const { return m_json_fstring_ref[1] == empty_json_array[1]; }
    void clear() { m_json_fstring_ref = empty_json_array; m_num_subs = 0; }
};


template<size_t STRING_CAPACITY=511>
class DllExport object_json_creator : public sub_object_json_creator
{
public:
    object_json_creator() noexcept
    : sub_object_json_creator(m_fstr, PreventAmbiguityOnConstructorCalls())
    {}

protected:
    fixed::fstring_base<STRING_CAPACITY, char> m_fstr{empty_json_object};
};

template<size_t STRING_CAPACITY=511>
class DllExport array_json_creator : public sub_array_json_creator
{
public:
    array_json_creator() noexcept
    : sub_array_json_creator(m_fstr, PreventAmbiguityOnConstructorCalls())
    {}

protected:
    fixed::fstring_base<STRING_CAPACITY, char> m_fstr{empty_json_array};
};

inline std::ostream& operator<<(std::ostream& os, const base_json_creator in_j_c)
{
    const std::string_view as_sv(in_j_c);
    os << as_sv;
    return os;
}


} // namespace fixed

#endif // __json_creator_h__
