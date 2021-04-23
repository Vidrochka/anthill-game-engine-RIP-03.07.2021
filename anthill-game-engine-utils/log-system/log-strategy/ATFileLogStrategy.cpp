#include "ATFileLogStrategy.hpp"

#include "../ATLoggerDefineExtensions.hpp"
#include "../ATLoggerExceptions.hpp"
#include "ATLoggerStrategyUtils.hpp"

using namespace at::utils::log_system::event;
using namespace at::type::string;

namespace at::utils::log_system::strategy
{
    FileLogStrategy::FileLogStrategy(u8string_at file_path, size_t buffer_size) : _buffer_size(buffer_size) {
        _file_path = file_path;
        _file_stream = std::ofstream{file_path, std::ios::app};

        if (!_file_stream.is_open())
            throw log_system::exceptions::log_file_unawalable_exception("Can't open required file"u8at, _file_path);
    }

    FileLogStrategy::~FileLogStrategy() {
        _file_stream.flush();
        _file_stream.close();
    }

    auto FileLogStrategy::log(log_msg::LogMsg log_msg) -> void {
        u8string_at pre_log_buffer;
        pre_log_buffer += log_utils::_get_datetime_prefix() + " "u8at;

        switch (log_msg.event_type)
        {
        case EVENT_TYPE::LOG_DEBUG:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::LOG_DEBUG>);
            break;
        case EVENT_TYPE::LOG_INFO:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::LOG_INFO>);
            break;
        case EVENT_TYPE::LOG_WARNING:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::LOG_WARNING>);
            break;
        case EVENT_TYPE::LOG_ERROR:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::LOG_ERROR>);
            break;
        case EVENT_TYPE::LOG_FATAL:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::LOG_FATAL>);
            break;
        }

        pre_log_buffer += "\n -> \"message\": \""u8at + log_msg.msg + "\""u8at;

        if (log_msg.has_error_code)
            pre_log_buffer += "\n -> \"error_code\": "u8at + int_to_u8_at(log_msg.error_code);

        if (log_msg.has_stack_trace)
            pre_log_buffer += "\n -> \"stack_trace\":\n"u8at + boost::stacktrace::to_string(log_msg.stack_trace) + "\n\n"u8at;
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

    auto FileLogStrategy::flush() -> void {
        _file_stream << _log_buffer.str();
        _file_stream.flush();
        _log_buffer.str(u8string_at());
    }
}