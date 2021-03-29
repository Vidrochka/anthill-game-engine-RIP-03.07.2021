#ifndef at_logger
#define at_logger

#include "ATLoggerStrategy.hpp"
#include "ATLoggerContext.hpp"

#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <mutex>
#include <vector>
#include <functional>

using namespace at::utils::logger_manager::strategy;
using namespace at::utils::logger_manager::strategy::interface;

namespace at::utils::logger_manager::logger
{
    namespace interface
    {
        class ILogger
        {
        public:
            //log debug to corrent logger
            virtual void log_debug(std::wstring msg, std::wstring log_poin = L"") = 0;
            //log info to corrent logger
            virtual void log_info(std::wstring msg, std::wstring log_poin = L"") = 0;
            //log debug to corrent logger
            virtual void log_warning(std::wstring msg, std::wstring log_poin = L"") = 0;
            //log error to corrent logger
            virtual void log_error(std::wstring msg, std::wstring log_poin = L"") = 0;
            //log fatal to corrent logger
            virtual void log_fatal(std::wstring msg, int error_code, std::wstring log_poin = L"") = 0;
            //flush corrent logger_section
            virtual void flush() = 0;

            virtual void add_strategy(ILogStrategy *strategy) = 0;
        };
    }

    class DefaultLogger : public interface::ILogger
    {
    private:
        void _log(std::wstring msg, event::EVENT_TYPE event_type, std::wstring log_poin = L"");
        void _flush();
        void _add_strategy(ILogStrategy *strategy);

        logger_context::LoggerContext *_logger_context = nullptr;

    public:
        //logger with logging in log_section
        DefaultLogger(logger_context::LoggerContext *logger_info);
        ~DefaultLogger();

        //log debug to corrent logger
        void log_debug(std::wstring msg, std::wstring log_poin = L"") override;
        //log info to corrent logger
        void log_info(std::wstring msg, std::wstring log_poin = L"") override;
        //log debug to corrent logger
        void log_warning(std::wstring msg, std::wstring log_poin = L"") override;
        //log error to corrent logger
        void log_error(std::wstring msg, std::wstring log_poin = L"") override;
        //log fatal to corrent logger
        void log_fatal(std::wstring msg, int error_code, std::wstring log_poin = L"") override;

        void flush() override;

        void add_strategy(ILogStrategy *strategy = new DefaultFileLogStrategy{}) override;
    };
}

#endif
