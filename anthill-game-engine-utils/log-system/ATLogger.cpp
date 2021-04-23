#include "ATLogger.hpp"
#include "ATLogMsg.hpp"

#include "../../third-party-libs/boost_1_75_0/boost/stacktrace.hpp"

#include <ctime>
#include <stdexcept>

using namespace at::utils::log_system::strategy;
using namespace at::utils::log_system::strategy::at_interface;
using namespace at::type::string;

namespace at::utils::log_system::logger
{
    auto DefaultLogger::_log(log_msg::LogMsg log_msg) -> void {
        std::lock_guard<std::mutex> lg(_logger_context->write_mutex);

        for (auto strategy : _logger_context->strategy_list)
            strategy->log(log_msg);
    }

    auto DefaultLogger::_flush() -> void {
        std::lock_guard<std::mutex> lg(_logger_context->write_mutex);

        for (auto strategy : _logger_context->strategy_list)
            strategy->flush();
    }

    auto DefaultLogger::_add_strategy(std::shared_ptr<ILogStrategy> strategy) -> void {
        std::lock_guard<std::mutex> lg(_logger_context->write_mutex);
        _logger_context->strategy_list.push_back(strategy);
    }

    DefaultLogger::DefaultLogger(std::shared_ptr<logger_context::LoggerContext> context) : at_interface::ILogger(context) {
    }

    DefaultLogger::~DefaultLogger() {
        flush();
    }

    auto DefaultLogger::log_debug(u8string_at msg, bool is_need_stack_trace) -> void {
#if defined(_DEBUG) || defined(DEBUG)
        log_msg::LogMsg log_msg{
            msg,
            event::EVENT_TYPE::LOG_DEBUG,
            false,
            0,
            is_need_stack_trace
        };

        if (is_need_stack_trace)
            log_msg.stack_trace = boost::stacktrace::stacktrace();

        _log(log_msg);
#endif // _DEBUG 
    }

    auto DefaultLogger::log_info(u8string_at msg, bool is_need_stack_trace) -> void {
        log_msg::LogMsg log_msg{
            msg,
            event::EVENT_TYPE::LOG_INFO,
            false,
            0,
            is_need_stack_trace
        };

        if (is_need_stack_trace)
            log_msg.stack_trace = boost::stacktrace::stacktrace();

        _log(log_msg);
    }

    auto DefaultLogger::log_warning(u8string_at msg, bool is_need_stack_trace) -> void {
        log_msg::LogMsg log_msg{
            msg,
            event::EVENT_TYPE::LOG_WARNING,
            false,
            0,
            is_need_stack_trace
        };

        if (is_need_stack_trace)
            log_msg.stack_trace = boost::stacktrace::stacktrace();

        _log(log_msg);
    }

    auto DefaultLogger::log_error(u8string_at msg, bool is_need_stack_trace) -> void {
        log_msg::LogMsg log_msg{
            msg,
            event::EVENT_TYPE::LOG_ERROR,
            false,
            0,
            is_need_stack_trace
        };

        if (is_need_stack_trace)
            log_msg.stack_trace = boost::stacktrace::stacktrace();

        _log(log_msg);
    }

    auto DefaultLogger::log_fatal(u8string_at msg, int error_code, bool is_need_stack_trace) -> void {
        log_msg::LogMsg log_msg{
            msg,
            event::EVENT_TYPE::LOG_FATAL,
            true,
            error_code,
            is_need_stack_trace
        };

        if (is_need_stack_trace)
            log_msg.stack_trace = boost::stacktrace::stacktrace();

        _log(log_msg);
        _flush();
    }

    auto DefaultLogger::flush() -> void {
        _flush();
    }

    auto DefaultLogger::add_strategy(std::shared_ptr<ILogStrategy> strategy) -> void {
        _add_strategy(strategy);
    }
}
