#ifndef at_logger
#define at_logger

#include "ATLoggerStrategy.hpp"
#include "ATLoggerContext.hpp"
#include "../Types/ATString.hpp"

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
            ILogger(std::shared_ptr<logger_context::LoggerContext> context)
            {
                _logger_context = context;
            }
            virtual ~ILogger(){};
            //log debug to corrent logger
            virtual void log_debug(u8string_at msg, u8string_at log_poin = "") = 0;
            //log info to corrent logger
            virtual void log_info(u8string_at msg, u8string_at log_poin = "") = 0;
            //log debug to corrent logger
            virtual void log_warning(u8string_at msg, u8string_at log_poin = "") = 0;
            //log error to corrent logger
            virtual void log_error(u8string_at msg, u8string_at log_poin = "") = 0;
            //log fatal to corrent logger
            virtual void log_fatal(u8string_at msg, int error_code, u8string_at log_poin = "") = 0;
            //flush corrent logger_section
            virtual void flush() = 0;

            virtual void add_strategy(ILogStrategy *strategy) = 0;
        };
    }

    class DefaultLogger : public at_interface::ILogger
    {
    private:
        void _log(u8string_at msg, event::EVENT_TYPE event_type, u8string_at log_poin = "");
        void _flush();
        void _add_strategy(ILogStrategy *strategy);

    public:
        //logger with logging in log_section
        DefaultLogger(std::shared_ptr<logger_context::LoggerContext> context);
        ~DefaultLogger() override;

        //log debug to corrent logger
        void log_debug(u8string_at msg, u8string_at log_poin = "") override;
        //log info to corrent logger
        void log_info(u8string_at msg, u8string_at log_poin = "") override;
        //log debug to corrent logger
        void log_warning(u8string_at msg, u8string_at log_poin = "") override;
        //log error to corrent logger
        void log_error(u8string_at msg, u8string_at log_poin = "") override;
        //log fatal to corrent logger
        void log_fatal(u8string_at msg, int error_code, u8string_at log_poin = "") override;

        void flush() override;

        void add_strategy(ILogStrategy *strategy = new DefaultFileLogStrategy{}) override;
    };
}

#endif
