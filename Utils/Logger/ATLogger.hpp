#ifndef at_logger
#define at_logger

#include "ATLoggerStrategy.hpp"

#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <mutex>
#include <vector>
#include <functional>

namespace at::utils::logger
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
            virtual void log_fatal(std::wstring msg, int exit_code, std::wstring log_poin = L"") = 0;
            //flush corrent logger_section
            virtual void flush() = 0;

            virtual void add_strategy(strategy::interface::ILogStrategy *strategy) = 0;
        };
    }
    namespace inner
    {
        struct LoggerInfo
        {
        public:
            LoggerInfo() {}
            LoggerInfo(at::utils::logger::strategy::interface::ILogStrategy *strategy)
                : strategy_list(std::vector{strategy})
            {
            }
            std::vector<at::utils::logger::strategy::interface::ILogStrategy *> strategy_list;
            std::mutex write_mutex{};
        };
    }

    class ATLogger : public interface::ILogger
    {
    private:
        // log_section : {file_path, log_buffer, mutex}
        static std::map<std::wstring, inner::LoggerInfo *> _log_buffer_map;
        static std::mutex *_add_new_section_mutex;
        static void _log(inner::LoggerInfo *log_section, std::wstring msg, logger::event::EVENT_TYPE event_type, std::wstring log_poin = L"");
        static void _log(std::wstring log_section, std::wstring msg, logger::event::EVENT_TYPE event_type, std::wstring log_poin = L"");
        static void _flush(inner::LoggerInfo *log_section);
        static void _flush_all();
        static void _flush(std::wstring log_section);
        static void _add_strategy(strategy::interface::ILogStrategy *strategy, inner::LoggerInfo *log_section);
        static void _add_strategy(strategy::interface::ILogStrategy *strategy, std::wstring log_section);

        inner::LoggerInfo *_logger_section = nullptr;

    public:
        //logger with logging in log_section
        ATLogger(std::wstring log_section);
        //logger with default logsettings
        ATLogger();
        ~ATLogger();

        //log debug to base logger
        static void b_log_debug(std::wstring msg, std::wstring log_poin = L"");
        //log info to base logger
        static void b_log_info(std::wstring msg, std::wstring log_poin = L"");
        //log debug to base logger
        static void b_log_warning(std::wstring msg, std::wstring log_poin = L"");
        //log error to base logger
        static void b_log_error(std::wstring msg, std::wstring log_poin = L"");
        //log fatal to base logger and exit with exit_code
        static void b_log_fatal(std::wstring msg, int exit_code, std::wstring log_poin = L"");
        //log args
        static void b_log_args(std::wstring args, int count, std::wstring log_poin = L"");

        //log debug to corrent logger
        void log_debug(std::wstring msg, std::wstring log_poin = L"") override;
        //log info to corrent logger
        void log_info(std::wstring msg, std::wstring log_poin = L"") override;
        //log debug to corrent logger
        void log_warning(std::wstring msg, std::wstring log_poin = L"") override;
        //log error to corrent logger
        void log_error(std::wstring msg, std::wstring log_poin = L"") override;
        //log fatal to corrent logger
        void log_fatal(std::wstring msg, int exit_code, std::wstring log_poin = L"") override;

        //flush base logger
        static void b_flush();
        //flush log_section
        static void flush(std::wstring log_section);
        //flush corrent logger_section
        void flush() override;

        static void b_add_strategy(strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{});
        static void add_strategy(strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{}, std::wstring log_section = L"");
        void add_strategy(strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{}) override;
        //create base logger section
        static void init_base_logger(strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{}, bool throw_if_exist = true);
        //check existanse log section;
        //if need_create_if_not_exist == true create and return false;
        //if need_create_if_not_exist == false and not exist return false;
        //if need_create_if_not_exist == anything and exist return true
        static bool is_section_exist(std::wstring log_section = L"", bool need_create_if_not_exist = false, strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{});
        static void create_section(std::wstring log_section, strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{}, bool throw_if_exist = true);
    };
}

#endif