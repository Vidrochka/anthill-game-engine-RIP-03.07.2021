#include "ATLoggerStrategy.hpp"
#include "ATLoggerDefineExtensions.hpp"
#include <ctime>

using namespace at::utils::log_system::event;
using namespace at::type::string;

namespace at::utils::log_system::strategy
{
    namespace log_utils
    {
        u8string_at _get_datetime_prefix()
        {
            time_t now = time(0);
#pragma warning(suppress : 4996)
            std::string raw_dt{ctime(&now)};
            u8string_at s_dt = u8string_at(raw_dt.begin(), raw_dt.end());
            return "[" + s_dt.substr(0, s_dt.length() - 1) + "]";
        }
    }

    DefaultFileLogStrategy::DefaultFileLogStrategy(u8string_at file_path, size_t buffer_size)
        : _buffer_size(buffer_size)
    {
        _file_path = file_path;
        _file_stream = std::ofstream{file_path, std::ios::app};

        if (!_file_stream.is_open())
            throw u8string_at("Log file not opened: ") + _file_path;
    }

    DefaultFileLogStrategy::~DefaultFileLogStrategy()
    {
        _file_stream.flush();
        _file_stream.close();
    }

    void DefaultFileLogStrategy::Log(EVENT_TYPE event_type, u8string_at msg, u8string_at log_poin)
    {
        u8string_at pre_log_buffer;
        pre_log_buffer += log_utils::_get_datetime_prefix();

        switch (event_type)
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

        pre_log_buffer += "{ \"message\": \"" + msg + "\"";

        if (log_poin != "")
            pre_log_buffer += ", \"log point\": \"" + log_poin + "\" }\n";
        else
            pre_log_buffer += "}\n";

        _log_buffer << pre_log_buffer;

        _actual_buffer_filling += pre_log_buffer.size();

        if (_actual_buffer_filling >= _buffer_size)
        {
            _actual_buffer_filling = 0;
            Flush();
        }
    }

    void DefaultFileLogStrategy::Flush()
    {
        _file_stream << _log_buffer.str();
        _file_stream.flush();
        _log_buffer.str(u8string_at());
    }
}