#ifndef __universal_converter_h__
#define __universal_converter_h__

#include "fstring.h"

class universal_converter
{
public:
    
    universal_converter() = default;
    
    constexpr operator std::string_view() const  noexcept { return std::string_view(m_value); }

    template<typename TValue>
    universal_converter& operator=(const TValue in_value)
    {
        if constexpr (std::is_same<TValue, bool>())
        {
            m_value += in_value ? "true" : "false";
        }
        else if constexpr (std::is_same<TValue, char>())
        {
            m_value += in_value;
        }
        else if constexpr (std::is_floating_point_v<TValue>) {
            m_value.printf(in_value);
        }
        else if constexpr (std::is_integral_v<TValue> && std::is_signed_v<TValue>) {
            m_value.printf(in_value);
        }
        else if constexpr (std::is_integral_v<TValue> && std::is_unsigned_v<TValue>) {
            m_value.printf(in_value);
        }
        else if constexpr (std::is_convertible_v<TValue, std::string_view>){
            m_value += in_value;
        }
            
        return *this;
    }
    
protected:
    fstr::fstr63 m_value;
};

#endif // __universal_converter_h__
