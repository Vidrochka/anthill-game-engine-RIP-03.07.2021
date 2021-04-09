#include "ATString.hpp"

namespace at::type::string
{
    //----------------------------------------------//
    //----------------- int -> utf------------------//
    u8string_at int_to_u8_at(const int &val)
    {
        return std::to_string(val);
    }

    u16string_at int_to_u16_at(const int &val)
    {
        return at::type::string::u8_to_u16_at(std::to_string(val));
    }

    u32string_at int_to_u32_at(const int &val)
    {
        return at::type::string::u8_to_u32_at(std::to_string(val));
    }

    //----------------------------------------------//
    //----------------------------------------------//

    //----------------------------------------------//
    //----------------- double -> utf------------------//
    u8string_at double_to_u8_at(const double &val)
    {
        return std::to_string(val);
    }

    u16string_at double_to_u16_at(const double &val)
    {
        return at::type::string::u8_to_u16_at(std::to_string(val));
    }

    u32string_at double_to_u32_at(const double &val)
    {
        return at::type::string::u8_to_u32_at(std::to_string(val));
    }

    //----------------------------------------------//
    //----------------------------------------------//

    //-----------------------------------------------//
    //-----------------Trim section-----------------//

    u32string_at ltrim_at(u32string_at str, const u32string_at chars)
    {
        size_t pos = str.find_first_not_of(chars);

        if (pos == u32string_at::npos)
            return str;

        str.erase(0, pos);
        return str;
    }

    u32string_at rtrim_at(u32string_at str, const u32string_at chars)
    {
        size_t pos = str.find_last_not_of(chars);

        if (pos == u32string_at::npos)
            return str;

        str.erase(pos + 1);
        return str;
    }

    u32string_at trim_at(u32string_at str, const u32string_at chars)
    {
        return ltrim_at(rtrim_at(str, chars), chars);
    }

    //-----------------------------------------------//
    //-----------------------------------------------//
}