#include "ATLogger.hpp"
#include <ctime>
#include <stdexcept>

using namespace at::utils::logger_manager::strategy;
using namespace at::utils::logger_manager::strategy::interface;
using namespace at::type::string;

namespace at::utils::logger_manager::logger
{
    void DefaultLogger::_log(u8string_at msg, event::EVENT_TYPE event_type, u8string_at log_poin)
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

    void DefaultLogger::log_debug(u8string_at msg, u8string_at log_poin)
    {
        _log(msg, event::EVENT_TYPE::DEBUG, log_poin);
    }

    void DefaultLogger::log_info(u8string_at msg, u8string_at log_poin)
    {
        _log(msg, event::EVENT_TYPE::INFO, log_poin);
    }

    void DefaultLogger::log_warning(u8string_at msg, u8string_at log_poin)
    {
        _log(msg, event::EVENT_TYPE::WARNING, log_poin);
    }

    void DefaultLogger::log_error(u8string_at msg, u8string_at log_poin)
    {
        _log(msg, event::EVENT_TYPE::ERROR, log_poin);
    }

    void DefaultLogger::log_fatal(u8string_at msg, int error_code, u8string_at log_poin)
    {
        _log(msg + " | error code [" + int_to_u8_at(error_code) + "]", event::EVENT_TYPE::FATAL, log_poin);
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
