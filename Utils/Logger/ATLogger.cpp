#include "ATLogger.hpp"
#include <ctime>
#include <stdexcept>

namespace at::utils::logger
{
    std::map<std::wstring, inner::LoggerInfo *> ATLogger::_log_buffer_map{};
    std::mutex *ATLogger::_add_new_section_mutex = new std::mutex{};

    std::wstring _get_datetime_prefix();

    void ATLogger::_log(inner::LoggerInfo *log_section, std::wstring msg, logger::event::EVENT_TYPE event_type, std::wstring log_poin)
    {
        std::lock_guard<std::mutex> lg(log_section->write_mutex);
        for (auto strategy : log_section->strategy_list)
            strategy->Log(event_type, msg, log_poin);
    }

    void ATLogger::_log(std::wstring log_section, std::wstring msg, logger::event::EVENT_TYPE event_type, std::wstring log_poin)
    {
        _log(_log_buffer_map[log_section], msg, event_type);
    }

    void ATLogger::_flush_all()
    {
        for (auto log_info : _log_buffer_map)
            _flush(log_info.second);
    }

    void ATLogger::_flush(inner::LoggerInfo *log_section)
    {
        std::lock_guard<std::mutex> lg(log_section->write_mutex);

        for (auto strategy : log_section->strategy_list)
            strategy->Flush();
    }

    void ATLogger::_flush(std::wstring log_section)
    {
        _flush(_log_buffer_map[log_section]);
    }

    void ATLogger::_add_strategy(strategy::interface::ILogStrategy *strategy, inner::LoggerInfo *log_section)
    {
        std::lock_guard<std::mutex> lg(log_section->write_mutex);
        log_section->strategy_list.push_back(strategy);
    }

    void ATLogger::_add_strategy(strategy::interface::ILogStrategy *strategy, std::wstring log_section)
    {
        _add_strategy(strategy, _log_buffer_map[log_section]);
    }

    ATLogger::ATLogger(std::wstring log_section)
    {
        _logger_section = _log_buffer_map[log_section];
    }

    ATLogger::ATLogger()
    {
        _logger_section = _log_buffer_map[L""];
    }

    ATLogger::~ATLogger()
    {
        flush();
    }

    void ATLogger::b_log_debug(std::wstring msg, std::wstring log_poin)
    {
        _log(L"", msg, event::EVENT_TYPE::DEBUG, log_poin);
    }

    void ATLogger::b_log_info(std::wstring msg, std::wstring log_poin)
    {
        _log(L"", msg, event::EVENT_TYPE::INFO, log_poin);
    }

    void ATLogger::b_log_warning(std::wstring msg, std::wstring log_poin)
    {
        _log(L"", msg, event::EVENT_TYPE::WARNING, log_poin);
    }

    void ATLogger::b_log_error(std::wstring msg, std::wstring log_poin)
    {
        _log(L"", msg, event::EVENT_TYPE::ERROR, log_poin);
    }

    void ATLogger::b_log_fatal(std::wstring msg, int exit_code, std::wstring log_poin)
    {
        _log(L"", msg + L" | exit code [" + std::to_wstring(exit_code) + L"]", event::EVENT_TYPE::FATAL, log_poin);
        _flush_all();
        exit(exit_code);
    }

    void ATLogger::b_log_args(std::wstring args, int count, std::wstring log_poin)
    {
        _log(L"", args + L" | count [" + std::to_wstring(count) + L"]", event::EVENT_TYPE::DEBUG, log_poin);
    }

    void ATLogger::log_debug(std::wstring msg, std::wstring log_poin)
    {
        _log(_logger_section, msg, event::EVENT_TYPE::DEBUG, log_poin);
    }

    void ATLogger::log_info(std::wstring msg, std::wstring log_poin)
    {
        _log(_logger_section, msg, event::EVENT_TYPE::INFO, log_poin);
    }

    void ATLogger::log_warning(std::wstring msg, std::wstring log_poin)
    {
        _log(_logger_section, msg, event::EVENT_TYPE::WARNING, log_poin);
    }

    void ATLogger::log_error(std::wstring msg, std::wstring log_poin)
    {
        _log(_logger_section, msg, event::EVENT_TYPE::ERROR, log_poin);
    }

    void ATLogger::log_fatal(std::wstring msg, int exit_code, std::wstring log_poin)
    {
        _log(_logger_section, msg + L" | exit code [" + std::to_wstring(exit_code) + L"]", event::EVENT_TYPE::FATAL, log_poin);
        _flush_all();
        exit(exit_code);
    }

    void ATLogger::b_flush()
    {
        _flush(L"");
    }

    void ATLogger::flush(std::wstring log_section)
    {
        _flush(log_section);
    }

    void ATLogger::flush()
    {
        _flush(_logger_section);
    }

    void ATLogger::b_add_strategy(strategy::interface::ILogStrategy *strategy)
    {
        _add_strategy(strategy, L"");
    }

    void ATLogger::add_strategy(strategy::interface::ILogStrategy *strategy, std::wstring log_section)
    {
        _add_strategy(strategy, log_section);
    }

    void ATLogger::add_strategy(strategy::interface::ILogStrategy *strategy)
    {
        _add_strategy(strategy, _logger_section);
    }

    void ATLogger::init_base_logger(strategy::interface::ILogStrategy *strategy, bool throw_if_exist)
    {
        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        _log_buffer_map[L""] = new inner::LoggerInfo(strategy);
    }

    bool ATLogger::is_section_exist(std::wstring log_section, bool need_create_if_not_exist, strategy::interface::ILogStrategy *strategy)
    {
        if (_log_buffer_map.count(log_section) > 0)
            return true;

        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        if (need_create_if_not_exist)
            _log_buffer_map[log_section] = new inner::LoggerInfo(strategy);

        return false;
    }

    void ATLogger::create_section(std::wstring log_section, strategy::interface::ILogStrategy *strategy, bool throw_if_exist)
    {
        if (_log_buffer_map.count(log_section) > 0)
        {
            if (throw_if_exist)
                throw std::wstring(L"Log section already exist");
            else
                return;
        }

        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        _log_buffer_map[log_section] = new inner::LoggerInfo(strategy);
    }
}