#ifndef at_logger
#define at_logger

#include "ATLoggerStrategy.hpp"
#include "ATLoggerContext.hpp"
#include "../Types/ATString.hpp"
#include "log-strategy/ATFileLogStrategy.hpp"


#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <mutex>
#include <vector>
#include <functional>

using namespace at::utils::log_system::strategy;
using namespace at::utils::log_system::strategy::at_interface;
using namespace at::type::string;

namespace at::utils::log_system::logger
{
    namespace at_interface
    {
        class ILogger
        {
        protected:
            std::shared_ptr<logger_context::LoggerContext> _logger_context;

        private:
            ILogger();
            ILogger(ILogger &);

        public:
            ILogger(std::shared_ptr<logger_context::LoggerContext> context) {
                _logger_context = context;
            }
            virtual ~ILogger(){};
            //log debug to corrent logger
            virtual auto log_debug(u8string_at msg, bool is_need_stack_trace = false) -> void = 0;
            //log info to corrent logger
            virtual auto log_info(u8string_at msg, bool is_need_stack_trace = false) -> void = 0;
            //log debug to corrent logger
            virtual auto log_warning(u8string_at msg, bool is_need_stack_trace = true) -> void = 0;
            //log error to corrent logger
            virtual auto log_error(u8string_at msg, bool is_need_stack_trace = true) -> void = 0;
            //log fatal to corrent logger
            virtual auto log_fatal(u8string_at msg, int error_code, bool is_need_stack_trace = true) -> void = 0;
            //flush corrent logger_section
            virtual auto flush() -> void = 0;

            virtual auto add_strategy(std::shared_ptr<ILogStrategy> strategy) -> void = 0;
        };
    }

    class DefaultLogger : public at_interface::ILogger
    {
    private:
        auto _log(log_msg::LogMsg log_msg) -> void;
        auto _flush() -> void;
        auto _add_strategy(std::shared_ptr<ILogStrategy> strategy) -> void;

    public:
        //logger with logging in log_section
        DefaultLogger(std::shared_ptr<logger_context::LoggerContext> context);
        ~DefaultLogger() override;

        //log debug to corrent logger
        auto log_debug(u8string_at msg, bool is_need_stack_trace = false) -> void override;
        //log info to corrent logger
        auto log_info(u8string_at msg, bool is_need_stack_trace = false) -> void override;
        //log debug to corrent logger
        auto log_warning(u8string_at msg, bool is_need_stack_trace = true) -> void override;
        //log error to corrent logger
        auto log_error(u8string_at msg, bool is_need_stack_trace = true) -> void override;
        //log fatal to corrent logger
        auto log_fatal(u8string_at msg, int error_code, bool is_need_stack_trace = true) -> void override;

        auto flush() -> void override;

        auto add_strategy(std::shared_ptr<ILogStrategy> strategy = std::shared_ptr<ILogStrategy>(new FileLogStrategy{})) -> void override;
    };
}

#endif //at_logger
