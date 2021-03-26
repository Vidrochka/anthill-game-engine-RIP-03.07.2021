#ifndef at_logger
#define at_logger

//#include "ATMutex.hpp"

#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <mutex>

namespace at::utils::logger
{
    namespace inner
    {
        struct LoggerInfo
        {
        public:
            LoggerInfo() {}
            LoggerInfo(std::string fpath, int max_buffer_size)
                : fpath(fpath), max_buffer_size(max_buffer_size) {}
            std::string fpath{};
            std::stringstream buffer{};
            int max_buffer_size;
            std::mutex write_mutex{};
        };
    }

    class ATLogger
    {
    private:
        // log_section : {file_path, log_buffer, mutex}
        static std::map<std::string, inner::LoggerInfo *> _log_buffer_map;
        static std::mutex *_add_new_section_mutex;
        static void _log(inner::LoggerInfo *log_section, std::string msg);
        static void _log(std::string log_section, std::string msg);
        static void _flush(inner::LoggerInfo *log_section);
        static void _flush_all();
        static void _flush(std::string log_section);
        static void _set_new_log_path(inner::LoggerInfo *log_section, std::string fpath);
        static void _set_new_log_path(std::string log_section, std::string fpath);

        inner::LoggerInfo *_logger_section = nullptr;

    public:
        //logger with logging in log_section
        ATLogger(std::string log_section);
        //logger with default logsettings
        ATLogger();
        ~ATLogger();

        //set to base section
        static void b_set_new_log_path(std::string fpath);
        //set to defined section
        void set_new_log_path(std::string log_section, std::string fpath);
        //set to current section
        void set_new_log_path(std::string fpath);

        //log info to base logger
        static void b_log_info(std::string msg);
        //log debug to base logger
        static void b_log_debug(std::string msg);
        //log error to base logger
        static void b_log_error(std::string msg);
        //log fatal to base logger and exit with exit_code
        static void b_log_fatal(std::string msg, int exit_code);
        //log args
        static void b_log_args(std::string args, int count);

        //log info to corrent logger
        void log_info(std::string msg);
        //log debug to corrent logger
        void log_debug(std::string msg);
        //log error to corrent logger
        void log_error(std::string msg);
        //log fatal to corrent logger
        void log_fatal(std::string msg, int exit_code);

        //flush base logger
        static void b_flush();
        //flush log_section
        static void flush(std::string log_section);
        //flush corrent logger_section
        void flush();

        //create base logger section
        static void init_base_logger(int buffer_size = 1024, std::string fpath = "./default.log", bool throw_if_exist = true);
        //check existanse log section;
        //if need_create_if_not_exist == true create and return false;
        //if need_create_if_not_exist == false and not exist return false;
        //if need_create_if_not_exist == anything and exist return true
        static bool is_section_exist(std::string log_section = "", bool need_create_if_not_exist = false, std::string fpath = "./default.log", int buffer_size = 1024);
        static void create_section(std::string log_section, std::string fpath = "./default.log", int buffer_size = 1024, bool throw_if_exist = true);
    };
}

#endif