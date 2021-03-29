#include "ATLogger.hpp"
#include <ctime>
#include <stdexcept>

using namespace at::utils::logger_manager::strategy;
using namespace at::utils::logger_manager::strategy::interface;

namespace at::utils::logger_manager::logger
{
    void DefaultLogger::_log(std::wstring msg, event::EVENT_TYPE event_type, std::wstring log_poin)
    {
        std::lock_guard<std::mutex> lg(_logger_context->write_mutex);
        for (auto strategy : _logger_context->strategy_list)
            strategy->Log(event_type, msg, log_poin);
    }

    void DefaultLogger::_flush()
    {
        std::lock_guard<std::mutex> lg(_logger_context->write_mutex);

        for (auto strategy : _logger_context->strategy_list)
            strategy->Flush();
    }

    void DefaultLogger::_add_strategy(ILogStrategy *strategy)
    {
        std::lock_guard<std::mutex> lg(_logger_context->write_mutex);
        _logger_context->strategy_list.push_back(strategy);
    }

    DefaultLogger::DefaultLogger(logger_context::LoggerContext *logger_info)
    {
        _logger_context = logger_info;
    }

    DefaultLogger::~DefaultLogger()
    {
        flush();
    }

    void DefaultLogger::log_debug(std::wstring msg, std::wstring log_poin)
    {
        _log(msg, event::EVENT_TYPE::DEBUG, log_poin);
    }

    void DefaultLogger::log_info(std::wstring msg, std::wstring log_poin)
    {
        _log(msg, event::EVENT_TYPE::INFO, log_poin);
    }

    void DefaultLogger::log_warning(std::wstring msg, std::wstring log_poin)
    {
        _log(msg, event::EVENT_TYPE::WARNING, log_poin);
    }

    void DefaultLogger::log_error(std::wstring msg, std::wstring log_poin)
    {
        _log(msg, event::EVENT_TYPE::ERROR, log_poin);
    }

    void DefaultLogger::log_fatal(std::wstring msg, int error_code, std::wstring log_poin)
    {
        _log(msg + L" | error code [" + std::to_wstring(error_code) + L"]", event::EVENT_TYPE::FATAL, log_poin);
        _flush();
    }

    void DefaultLogger::flush()
    {
        _flush();
    }

    void DefaultLogger::add_strategy(ILogStrategy *strategy)
    {
        _add_strategy(strategy);
    }
}
