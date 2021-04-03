#ifndef at_string
#define at_string

#include <string>
#include <locale>
#include <codecvt>

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#define TO_STRING(obj) u8string_at(#obj)

namespace at::type::string
{
    //typedef std::basic_string<char8_t, std::char_traits<char8_t>, std::allocator<char8_t>> u8string_at;
    typedef std::string u8string_at;
    typedef std::u16string u16string_at;
    typedef std::u32string u32string_at;

    static u8string_at u16_to_u8_at(const u16string_at &s)
    {
#pragma warning(suppress : 4996)
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
#pragma warning(suppress : 4996)
        return conv.to_bytes(s);
    }

    static u8string_at u32_to_u8_at(const u32string_at &s)
    {
#pragma warning(suppress : 4996)
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
#pragma warning(suppress : 4996)
        return conv.to_bytes(s);
    }

    static u16string_at u8_to_u16_at(const u8string_at &s)
    {
#pragma warning(suppress : 4996)
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
#pragma warning(suppress : 4996)
        return conv.from_bytes(s);
    }

    static u16string_at u32_to_u16_at(const u32string_at &s)
    {
#pragma warning(suppress : 4996)
        std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> conv;
#pragma warning(suppress : 4996)
        std::string bytes = conv.to_bytes(s);
        return std::u16string(reinterpret_cast<const char16_t *>(bytes.c_str()), bytes.length() / sizeof(char16_t));
    }

    static u32string_at u8_to_u32_at(const u8string_at &s)
    {
#pragma warning(suppress : 4996)
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
#pragma warning(suppress : 4996)
        return conv.from_bytes(s);
    }

    static u32string_at u16_to_u32_at(const u16string_at &s)
    {
        const char16_t *pData = s.c_str();

#pragma warning(suppress : 4996)
        std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> conv;
#pragma warning(suppress : 4996)
        return conv.from_bytes(reinterpret_cast<const char *>(pData), reinterpret_cast<const char *>(pData + s.length()));
    }

    //----------------- int -> utf------------------//
    static u8string_at int_to_u8_at(const int &val)
    {
        return std::to_string(val);
    }

    static u16string_at int_to_u16_at(const int &val)
    {
        return at::type::string::u8_to_u16_at(std::to_string(val));
    }

    static u32string_at int_to_u32_at(const int &val)
    {
        return at::type::string::u8_to_u32_at(std::to_string(val));
    }
}

#endif