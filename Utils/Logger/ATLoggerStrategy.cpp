#include "ATLoggerStrategy.hpp"
#include "ATLoggerDefineExtensions.hpp"
#include <ctime>

using namespace at::utils::logger_manager::event;

namespace at::utils::logger_manager::strategy
{
    namespace log_utils
    {
        std::wstring _get_datetime_prefix()
        {
            time_t now = time(0);
            std::string raw_dt{ctime(&now)};
            std::wstring s_dt = std::wstring(raw_dt.begin(), raw_dt.end());
            return L"[" + s_dt.substr(0, s_dt.length() - 1) + L"]";
        }
    }

    DefaultFileLogStrategy::DefaultFileLogStrategy(std::wstring file_path, size_t buffer_size)
        : _buffer_size(buffer_size)
    {
        _file_path = file_path;
        _file_stream = std::wofstream{file_path, std::ios::app};

        if (!_file_stream.is_open())
            throw std::wstring(L"Log file not opened: ") + _file_path;
    }

    DefaultFileLogStrategy::~DefaultFileLogStrategy()
    {
        _file_stream.flush();
        _file_stream.close();
    }

    void DefaultFileLogStrategy::Log(EVENT_TYPE event_type, std::wstring msg, std::wstring log_poin)
    {
        std::wstring pre_log_buffer;
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

        pre_log_buffer += L"{ \"message\": \"" + msg + L"\"";

        if (log_poin != L"")
            pre_log_buffer += L", \"log point\": \"" + log_poin + L"\" }\n";
        else
            pre_log_buffer += L"}\n";

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
        _log_buffer.str(std::wstring());
    }
}