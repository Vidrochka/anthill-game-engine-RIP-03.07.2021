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
            //log info to corrent logger
            virtual void log_info(std::string msg, std::string log_poin = "") = 0;
            //log debug to corrent logger
            virtual void log_debug(std::string msg, std::string log_poin = "") = 0;
            //log error to corrent logger
            virtual void log_error(std::string msg, std::string log_poin = "") = 0;
            //log fatal to corrent logger
            virtual void log_fatal(std::string msg, int exit_code, std::string log_poin = "") = 0;
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
        static std::map<std::string, inner::LoggerInfo *> _log_buffer_map;
        static std::mutex *_add_new_section_mutex;
        static void _log(inner::LoggerInfo *log_section, std::string msg, logger::event::EVENT_TYPE event_type, std::string log_poin = "");
        static void _log(std::string log_section, std::string msg, logger::event::EVENT_TYPE event_type, std::string log_poin = "");
        static void _flush(inner::LoggerInfo *log_section);
        static void _flush_all();
        static void _flush(std::string log_section);
        static void _add_strategy(strategy::interface::ILogStrategy *strategy, inner::LoggerInfo *log_section);
        static void _add_strategy(strategy::interface::ILogStrategy *strategy, std::string log_section);

        inner::LoggerInfo *_logger_section = nullptr;

    public:
        //logger with logging in log_section
        ATLogger(std::string log_section);
        //logger with default logsettings
        ATLogger();
        ~ATLogger();

        //log info to base logger
        static void b_log_info(std::string msg, std::string log_poin = "");
        //log debug to base logger
        static void b_log_debug(std::string msg, std::string log_poin = "");
        //log error to base logger
        static void b_log_error(std::string msg, std::string log_poin = "");
        //log fatal to base logger and exit with exit_code
        static void b_log_fatal(std::string msg, int exit_code, std::string log_poin = "");
        //log args
        static void b_log_args(std::string args, int count, std::string log_poin = "");

        //log info to corrent logger
        void log_info(std::string msg, std::string log_poin = "") override;
        //log debug to corrent logger
        void log_debug(std::string msg, std::string log_poin = "") override;
        //log error to corrent logger
        void log_error(std::string msg, std::string log_poin = "") override;
        //log fatal to corrent logger
        void log_fatal(std::string msg, int exit_code, std::string log_poin = "") override;

        //flush base logger
        static void b_flush();
        //flush log_section
        static void flush(std::string log_section);
        //flush corrent logger_section
        void flush() override;

        static void b_add_strategy(strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{});
        static void add_strategy(strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{}, std::string log_section = "");
        void add_strategy(strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{}) override;
        //create base logger section
        static void init_base_logger(strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{}, bool throw_if_exist = true);
        //check existanse log section;
        //if need_create_if_not_exist == true create and return false;
        //if need_create_if_not_exist == false and not exist return false;
        //if need_create_if_not_exist == anything and exist return true
        static bool is_section_exist(std::string log_section = "", bool need_create_if_not_exist = false, strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{});
        static void create_section(std::string log_section, strategy::interface::ILogStrategy *strategy = new strategy::DefaultFileLogStrategy{}, bool throw_if_exist = true);
    };
}

#endif