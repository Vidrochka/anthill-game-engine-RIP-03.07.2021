#include "ATLogger.hpp"
#include <ctime>
#include <stdexcept>

namespace at::utils::logger
{
    std::map<std::string, inner::LoggerInfo *> ATLogger::_log_buffer_map{};
    std::mutex *ATLogger::_add_new_section_mutex = new std::mutex{};

    std::string _get_datetime_prefix();

    void ATLogger::_log(inner::LoggerInfo *log_section, std::string msg, logger::event::EVENT_TYPE event_type, std::string log_poin)
    {
        std::lock_guard<std::mutex> lg(log_section->write_mutex);
        for (auto strategy : log_section->strategy_list)
            strategy->Log(event_type, msg, log_poin);
    }

    void ATLogger::_log(std::string log_section, std::string msg, logger::event::EVENT_TYPE event_type, std::string log_poin)
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

    void ATLogger::_flush(std::string log_section)
    {
        _flush(_log_buffer_map[log_section]);
    }

    void ATLogger::_add_strategy(strategy::interface::ILogStrategy *strategy, inner::LoggerInfo *log_section)
    {
        std::lock_guard<std::mutex> lg(log_section->write_mutex);
        log_section->strategy_list.push_back(strategy);
    }

    void ATLogger::_add_strategy(strategy::interface::ILogStrategy *strategy, std::string log_section)
    {
        _add_strategy(strategy, _log_buffer_map[log_section]);
    }

    ATLogger::ATLogger(std::string log_section)
    {
        _logger_section = _log_buffer_map[log_section];
    }

    ATLogger::ATLogger()
    {
        _logger_section = _log_buffer_map[""];
    }

    ATLogger::~ATLogger()
    {
        flush();
    }

    void ATLogger::b_log_debug(std::string msg, std::string log_poin)
    {
        _log("", msg, event::EVENT_TYPE::DEBUG, log_poin);
    }

    void ATLogger::b_log_info(std::string msg, std::string log_poin)
    {
        _log("", msg, event::EVENT_TYPE::INFO, log_poin);
    }

    void ATLogger::b_log_warning(std::string msg, std::string log_poin)
    {
        _log("", msg, event::EVENT_TYPE::WARNING, log_poin);
    }

    void ATLogger::b_log_error(std::string msg, std::string log_poin)
    {
        _log("", msg, event::EVENT_TYPE::ERROR, log_poin);
    }

    void ATLogger::b_log_fatal(std::string msg, int exit_code, std::string log_poin)
    {
        _log("", msg + " | exit code [" + std::to_string(exit_code) + "]", event::EVENT_TYPE::FATAL, log_poin);
        _flush_all();
        exit(exit_code);
    }

    void ATLogger::b_log_args(std::string args, int count, std::string log_poin)
    {
        _log("", args + " | count [" + std::to_string(count) + "]", event::EVENT_TYPE::DEBUG, log_poin);
    }

    void ATLogger::log_debug(std::string msg, std::string log_poin)
    {
        _log(_logger_section, msg, event::EVENT_TYPE::DEBUG, log_poin);
    }

    void ATLogger::log_info(std::string msg, std::string log_poin)
    {
        _log(_logger_section, msg, event::EVENT_TYPE::INFO, log_poin);
    }

    void ATLogger::log_warning(std::string msg, std::string log_poin)
    {
        _log(_logger_section, msg, event::EVENT_TYPE::WARNING, log_poin);
    }

    void ATLogger::log_error(std::string msg, std::string log_poin)
    {
        _log(_logger_section, msg, event::EVENT_TYPE::ERROR, log_poin);
    }

    void ATLogger::log_fatal(std::string msg, int exit_code, std::string log_poin)
    {
        _log(_logger_section, msg + " | exit code [" + std::to_string(exit_code) + "]", event::EVENT_TYPE::FATAL, log_poin);
        _flush_all();
        exit(exit_code);
    }

    void ATLogger::b_flush()
    {
        _flush("");
    }

    void ATLogger::flush(std::string log_section)
    {
        _flush(log_section);
    }

    void ATLogger::flush()
    {
        _flush(_logger_section);
    }

    void ATLogger::b_add_strategy(strategy::interface::ILogStrategy *strategy)
    {
        _add_strategy(strategy, "");
    }

    void ATLogger::add_strategy(strategy::interface::ILogStrategy *strategy, std::string log_section)
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

        _log_buffer_map[""] = new inner::LoggerInfo(strategy);
    }

    bool ATLogger::is_section_exist(std::string log_section, bool need_create_if_not_exist, strategy::interface::ILogStrategy *strategy)
    {
        if (_log_buffer_map.count(log_section) > 0)
            return true;

        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        if (need_create_if_not_exist)
            _log_buffer_map[log_section] = new inner::LoggerInfo(strategy);

        return false;
    }

    void ATLogger::create_section(std::string log_section, strategy::interface::ILogStrategy *strategy, bool throw_if_exist)
    {
        if (_log_buffer_map.count(log_section) > 0)
        {
            if (throw_if_exist)
                throw std::string("Log section already exist");
            else
                return;
        }

        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        _log_buffer_map[log_section] = new inner::LoggerInfo(strategy);
    }
}