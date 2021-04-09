#include "ATLogger.hpp"
#include <ctime>
#include <stdexcept>

using namespace at::utils::log_system::strategy;
using namespace at::utils::log_system::strategy::at_interface;
using namespace at::type::string;

namespace at::utils::log_system::logger
{
    bool is_valid_ref(logger_context::LoggerContext **ref);

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

    DefaultLogger::DefaultLogger(std::shared_ptr<logger_context::LoggerContext> context) : at_interface::ILogger(context)
    {
    }

    DefaultLogger::~DefaultLogger()
    {
        flush();
    }

    void DefaultLogger::log_debug(u8string_at msg, u8string_at log_poin)
    {
        _log(msg, event::EVENT_TYPE::LOG_DEBUG, log_poin);
    }

    void DefaultLogger::log_info(u8string_at msg, u8string_at log_poin)
    {
        _log(msg, event::EVENT_TYPE::LOG_INFO, log_poin);
    }

    void DefaultLogger::log_warning(u8string_at msg, u8string_at log_poin)
    {
        _log(msg, event::EVENT_TYPE::LOG_WARNING, log_poin);
    }

    void DefaultLogger::log_error(u8string_at msg, u8string_at log_poin)
    {
        _log(msg, event::EVENT_TYPE::LOG_ERROR, log_poin);
    }

    void DefaultLogger::log_fatal(u8string_at msg, int error_code, u8string_at log_poin)
    {
        _log(msg + " | error code ["u8at + int_to_u8_at(error_code) + "]"u8at, event::EVENT_TYPE::LOG_FATAL, log_poin);
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

    bool is_valid_ref(logger_context::LoggerContext **ref)
    {
        return (*ref) != nullptr;
    }
}
