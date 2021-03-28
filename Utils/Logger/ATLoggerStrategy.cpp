#include "ATLoggerStrategy.hpp"
#include "ATLoggerDefineExtensions.hpp"
#include <ctime>

using namespace at::utils::logger::event;

namespace at::utils::logger::strategy
{
    namespace log_utils
    {
        std::string _get_datetime_prefix()
        {
            time_t now = time(0);
            char *dt = ctime(&now);
            std::string s_dt = std::string(dt);
            return "[" + s_dt.substr(0, s_dt.length() - 1) + "]";
        }
    }

    DefaultFileLogStrategy::DefaultFileLogStrategy(std::string file_path, size_t buffer_size)
        : _buffer_size(buffer_size)
    {
        _file_path = file_path;
        _file_stream = std::ofstream{file_path, std::ios::app};

        if (!_file_stream.is_open())
            throw std::string("Log file not opened: ") + _file_path;
    }

    DefaultFileLogStrategy::~DefaultFileLogStrategy()
    {
        _file_stream.flush();
        _file_stream.close();
    }

    void DefaultFileLogStrategy::Log(EVENT_TYPE event_type, std::string msg, std::string log_poin)
    {
        std::string pre_log_buffer;
        pre_log_buffer += log_utils::_get_datetime_prefix();

        switch (event_type)
        {
        case EVENT_TYPE::DEBUG:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::DEBUG>);
            break;
        case EVENT_TYPE::INFO:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::INFO>);
            break;
        case EVENT_TYPE::WARNING:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::WARNING>);
            break;
        case EVENT_TYPE::ERROR:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::ERROR>);
            break;
        case EVENT_TYPE::FATAL:
            pre_log_buffer += TO_STRING(<EVENT_TYPE::FATAL>);
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
        _log_buffer.str(std::string());
    }
}