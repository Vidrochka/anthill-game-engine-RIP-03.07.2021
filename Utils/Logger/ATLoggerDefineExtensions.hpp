#ifndef at_logger_define_extensions
#define at_logger_define_extensions
#include <sstream>
#include <string>
#include "ATLogger.hpp"

#define TO_STRING(obj) std::wstring(L#obj)

inline std::wstring cast_to_wsring(std::string str)
{
    return std::wstring(str.begin(), str.end());
}

#define LINE_STAMP std::wstring(L"Line stamp: ") + L"{ \"file\": \"" + cast_to_wsring(__FILE__) + L"\", \"function\": \"" + cast_to_wsring(__FUNCTION__) + L"\", \"line\": \"" + std::to_wstring(__LINE__) + L"\" }"

#define LOG_ARGS1(arg1)                                                      \
    {                                                                        \
        std::wstringstream __tmp_args_stream{};                              \
        __tmp_args_stream << arg1;                                           \
        at::utils::logger::ATLogger::b_log_args(__tmp_args_stream.str(), 1); \
    }

#define LOG_ARGS2(arg1, arg2)                                                \
    {                                                                        \
        std::wstringstream __tmp_args_stream{};                              \
        __tmp_args_stream << arg1 << ",";                                    \
        __tmp_args_stream << arg2;                                           \
        at::utils::logger::ATLogger::b_log_args(__tmp_args_stream.str(), 2); \
    }

#define LOG_ARGS3(arg1, arg2, arg3)                                          \
    {                                                                        \
        std::wstringstream __tmp_args_stream{};                              \
        __tmp_args_stream << arg1 << ", ";                                   \
        __tmp_args_stream << arg2 << ", ";                                   \
        __tmp_args_stream << arg3;                                           \
        at::utils::logger::ATLogger::b_log_args(__tmp_args_stream.str(), 3); \
    }

#define LOG_ARGS4(arg1, arg2, arg3, arg4)                                    \
    {                                                                        \
        std::wstringstream __tmp_args_stream{};                              \
        __tmp_args_stream << arg1 << ", ";                                   \
        __tmp_args_stream << arg2 << ", ";                                   \
        __tmp_args_stream << arg3 << ", ";                                   \
        __tmp_args_stream << arg4;                                           \
        at::utils::logger::ATLogger::b_log_args(__tmp_args_stream.str(), 4); \
    }

#define LOG_ARGS5(arg1, arg2, arg3, arg4, arg5)                              \
    {                                                                        \
        std::wstringstream __tmp_args_stream{};                              \
        __tmp_args_stream << arg1 << ", ";                                   \
        __tmp_args_stream << arg2 << ", ";                                   \
        __tmp_args_stream << arg3 << ", ";                                   \
        __tmp_args_stream << arg4 << ", ";                                   \
        __tmp_args_stream << arg5;                                           \
        at::utils::logger::ATLogger::b_log_args(__tmp_args_stream.str(), 5); \
    }

#define LOG_ARGS6(arg1, arg2, arg3, arg4, arg5, arg6)                        \
    {                                                                        \
        std::wstringstream __tmp_args_stream{};                              \
        __tmp_args_stream << arg1 << ", ";                                   \
        __tmp_args_stream << arg2 << ", ";                                   \
        __tmp_args_stream << arg3 << ", ";                                   \
        __tmp_args_stream << arg4 << ", ";                                   \
        __tmp_args_stream << arg5 << ", ";                                   \
        __tmp_args_stream << arg6;                                           \
        at::utils::logger::ATLogger::b_log_args(__tmp_args_stream.str(), 6); \
    }

#define LOG_ARGS7(arg1, arg2, arg3, arg4, arg5, arg6, arg7)                  \
    {                                                                        \
        std::wstringstream __tmp_args_stream{};                              \
        __tmp_args_stream << arg2 << ", ";                                   \
        __tmp_args_stream << arg1 << ", ";                                   \
        __tmp_args_stream << arg3 << ", ";                                   \
        __tmp_args_stream << arg4 << ", ";                                   \
        __tmp_args_stream << arg5 << ", ";                                   \
        __tmp_args_stream << arg6 << ", ";                                   \
        __tmp_args_stream << arg7;                                           \
        at::utils::logger::ATLogger::b_log_args(__tmp_args_stream.str(), 7); \
    }

#define LOG_ARGS8(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)            \
    {                                                                        \
        std::wstringstream __tmp_args_stream{};                              \
        __tmp_args_stream << arg1 << ", ";                                   \
        __tmp_args_stream << arg2 << ", ";                                   \
        __tmp_args_stream << arg3 << ", ";                                   \
        __tmp_args_stream << arg4 << ", ";                                   \
        __tmp_args_stream << arg5 << ", ";                                   \
        __tmp_args_stream << arg6 << ", ";                                   \
        __tmp_args_stream << arg7 << ", ";                                   \
        __tmp_args_stream << arg8;                                           \
        at::utils::logger::ATLogger::b_log_args(__tmp_args_stream.str(), 8); \
    }

#endif