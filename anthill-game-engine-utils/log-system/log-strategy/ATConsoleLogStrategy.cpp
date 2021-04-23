#include "ATConsoleLogStrategy.hpp"

#include "../ATLoggerDefineExtensions.hpp"
#include "../ATLoggerExceptions.hpp"
#include "ATLoggerStrategyUtils.hpp"

#include <iostream>

#define RED_CONSOLE_COLOR(text) "\x1b[31m"u8at + text + "\x1b[0m"u8at
#define GREEN_CONSOLE_COLOR(text) "\x1b[32m"u8at + text + "\x1b[0m"u8at
#define ORANGE_CONSOLE_COLOR(text) "\x1b[33m"u8at + text + "\x1b[0m"u8at
#define YELOW_CONSOLE_COLOR(text) "\x1b[33;1m"u8at + text + "\x1b[0m"u8at
#define WHITE_CONSOLE_COLOR(text) "\x1b[37m"u8at + text + "\x1b[0m"u8at
#define MAGENTA_CONSOLE_COLOR(text) "\x1b[35m"u8at + text + "\x1b[0m"u8at
#define BLUE_CONSOLE_COLOR(text) "\x1b[34m"u8at + text + "\x1b[0m"u8at
#define CYAN_CONSOLE_COLOR(text) "\x1b[36m"u8at + text + "\x1b[0m"u8at
#define GRAY_CONSOLE_COLOR(text) "\x1b[30;1m"u8at + text + "\x1b[0m"u8at

using namespace at::utils::log_system::event;
using namespace at::type::string;

namespace at::utils::log_system::strategy
{
    ConsoleLogStrategy::ConsoleLogStrategy(size_t buffer_size) : _buffer_size(buffer_size) {
    }

    ConsoleLogStrategy::~ConsoleLogStrategy() {
    }

    auto ConsoleLogStrategy::log(log_msg::LogMsg log_msg) -> void {
        u8string_at pre_log_buffer;
        pre_log_buffer += GRAY_CONSOLE_COLOR(log_utils::_get_datetime_prefix()) + " "u8at;

        switch (log_msg.event_type)
        {
        case EVENT_TYPE::LOG_DEBUG:
            pre_log_buffer += WHITE_CONSOLE_COLOR(TO_STRING(<EVENT_TYPE::LOG_DEBUG>));
            //pre_log_buffer += "{\n\t"u8at + WHITE_CONSOLE_COLOR("\"message\""u8at) + ": \""u8at + WHITE_CONSOLE_COLOR(log_msg.msg) + "\""u8at;
            break;
        case EVENT_TYPE::LOG_INFO:
            pre_log_buffer += GREEN_CONSOLE_COLOR(TO_STRING(<EVENT_TYPE::LOG_INFO>));
            //pre_log_buffer += "{\n\t"u8at + GREEN_CONSOLE_COLOR("\"message\""u8at) + ": \""u8at + GREEN_CONSOLE_COLOR(log_msg.msg) + "\""u8at;
            break;
        case EVENT_TYPE::LOG_WARNING:
            pre_log_buffer += YELOW_CONSOLE_COLOR(TO_STRING(<EVENT_TYPE::LOG_WARNING>));
            //pre_log_buffer += "{\n\t"u8at + YELOW_CONSOLE_COLOR("\"message\""u8at) + ": \""u8at + YELOW_CONSOLE_COLOR(log_msg.msg) + "\""u8at;
            break;
        case EVENT_TYPE::LOG_ERROR:
            pre_log_buffer += RED_CONSOLE_COLOR(TO_STRING(<EVENT_TYPE::LOG_ERROR>));
            //pre_log_buffer += "{\n\t"u8at + RED_CONSOLE_COLOR("\"message\""u8at) + ": \""u8at + MAGENTA_CONSOLE_COLOR(log_msg.msg) + "\""u8at;
            break;
        case EVENT_TYPE::LOG_FATAL:
            pre_log_buffer += RED_CONSOLE_COLOR(TO_STRING(<EVENT_TYPE::LOG_FATAL>));
            //pre_log_buffer += "{\n\t"u8at + RED_CONSOLE_COLOR("\"message\""u8at) + ": \""u8at + MAGENTA_CONSOLE_COLOR(log_msg.msg) + "\""u8at;
            break;
        }

        pre_log_buffer += "\n -> "u8at + YELOW_CONSOLE_COLOR("\"message\""u8at) + ": \""u8at + log_msg.msg + "\""u8at;

        if (log_msg.has_error_code)
            pre_log_buffer += "\n -> "u8at + YELOW_CONSOLE_COLOR("\"error_code\""u8at) + ": "u8at + int_to_u8_at(log_msg.error_code);

        if (log_msg.has_stack_trace)
            pre_log_buffer += "\n -> "u8at + YELOW_CONSOLE_COLOR("\"stack_trace\""u8at) + ":\n"u8at + ORANGE_CONSOLE_COLOR(boost::stacktrace::to_string(log_msg.stack_trace)) + "\n\n"u8at;
        else
            pre_log_buffer += "\n\n"u8at;

        _log_buffer << pre_log_buffer;

        _actual_buffer_filling += pre_log_buffer.size();

        if (_actual_buffer_filling >= _buffer_size)
        {
            _actual_buffer_filling = 0;
            flush();
        }
    }

    auto ConsoleLogStrategy::flush() -> void
    {
        std::cout << _log_buffer.str() << std::flush;
        _log_buffer.str(u8string_at());
    }
}