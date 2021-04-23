#ifndef at_string
#define at_string

#include <string>
#include <locale>
#include <codecvt>
#include <regex>

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

    static u8string_at wstring_to_u8_at(const std::wstring &s)
    {
#pragma warning(suppress : 4996)
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;
#pragma warning(suppress : 4996)
        return conv.to_bytes(s);
    }

    //----------------------------------------------//
    //----------------- int -> utf------------------//
    u8string_at int_to_u8_at(const int &val);

    u16string_at int_to_u16_at(const int &val);

    u32string_at int_to_u32_at(const int &val);

    //----------------------------------------------//
    //----------------------------------------------//

    //----------------------------------------------//
    //----------------- double -> utf------------------//
    u8string_at double_to_u8_at(const double &val);

    u16string_at double_to_u16_at(const double &val);

    u32string_at double_to_u32_at(const double &val);

    //----------------------------------------------//
    //----------------------------------------------//

    //-----------------------------------------------//
    //-----------------Trim section-----------------//

    u32string_at ltrim_at(u32string_at str, const u32string_at chars);

    u32string_at rtrim_at(u32string_at str, const u32string_at chars);

    u32string_at trim_at(u32string_at str, const u32string_at chars);

    //-----------------------------------------------//
    //-----------------------------------------------//

    inline at::type::string::u8string_at operator"" u8at(const char* str, std::size_t len){
        return u8string_at(str, len);
    }

    inline at::type::string::u16string_at operator"" u16at(const char* str, std::size_t len){
        return u8_to_u16_at(u8string_at(str, len));
    }

    inline at::type::string::u32string_at operator"" u32at(const char* str, std::size_t len){
        return u8_to_u32_at(u8string_at(str, len));
    }

    //-----------------------------------------------//
    //-----------------String builder----------------//

    class U8StringBuilder
    {
    private:
        u8string_at _raw_string;
        U8StringBuilder() = delete;
        U8StringBuilder(const U8StringBuilder&) = delete;

    public:
        U8StringBuilder(u8string_at raw_string)
        {
            _raw_string = raw_string;
        }

        template<typename T>
        auto fmt(u8string_at regex, T formatter) -> U8StringBuilder&
        {
            std::regex r{regex};
            _raw_string = std::regex_replace(_raw_string, r, std::to_string(formatter));
            return *this;
        }

        template<>
        auto fmt(u8string_at regex, u8string_at formatter) -> U8StringBuilder& {
            std::regex r{regex};
            _raw_string = std::regex_replace(_raw_string, r, formatter);
            return *this;
        }

        template<>
        auto fmt(u8string_at regex, const char* formatter) -> U8StringBuilder& {
            std::regex r{regex};
            _raw_string = std::regex_replace(_raw_string, r, u8string_at(formatter));
            return *this;
        }

        template<>
        auto fmt(u8string_at regex, char* formatter) -> U8StringBuilder& {
            std::regex r{regex};
            _raw_string = std::regex_replace(_raw_string, r, u8string_at(formatter));
            return *this;
        }

        template<typename T>
        auto fmt(int param_number, T formatter) -> U8StringBuilder&
        {
            std::regex r{"\\{"u8at + int_to_u8_at(param_number) + "\\}"u8at};
            _raw_string = std::regex_replace(_raw_string, r, std::to_string(formatter));
            return *this;
        }

        
        template<>
        auto fmt(int param_number, u8string_at formatter) -> U8StringBuilder& {
            std::regex r{"\\{"u8at + int_to_u8_at(param_number) + "\\}"u8at};
            _raw_string = std::regex_replace(_raw_string, r, formatter);
            return *this;
        }

        template<>
        auto fmt(int param_number, const char* formatter) -> U8StringBuilder& {
            std::regex r{"\\{"u8at + int_to_u8_at(param_number) + "\\}"u8at};
            _raw_string = std::regex_replace(_raw_string, r, u8string_at(formatter));
            return *this;
        }

        template<>
        auto fmt(int param_number, char* formatter) -> U8StringBuilder& {
            std::regex r{"\\{"u8at + int_to_u8_at(param_number) + "\\}"u8at};
            _raw_string = std::regex_replace(_raw_string, r, u8string_at(formatter));
            return *this;
        }

        operator u8string_at() { return _raw_string; }
    };

    //-----------------------------------------------//
    //-----------------------------------------------//
}

#endif