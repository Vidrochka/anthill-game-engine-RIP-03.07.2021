#ifndef at_logger
#define at_logger

//#include "ATMutex.hpp"

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
            virtual void log_info(std::string msg) = 0;
            //log debug to corrent logger
            virtual void log_debug(std::string msg) = 0;
            //log error to corrent logger
            virtual void log_error(std::string msg) = 0;
            //log fatal to corrent logger
            virtual void log_fatal(std::string msg, int exit_code) = 0;
            //flush corrent logger_section
            virtual void flush() = 0;

            virtual void add_callback(std::function<void(std::string)> callback) = 0;
        };
    }
    namespace inner
    {
        struct LoggerInfo
        {
        public:
            LoggerInfo() {}
            LoggerInfo(std::string fpath, size_t max_buffer_size) : fpath(fpath), max_buffer_size(max_buffer_size) {}
            std::string fpath{};
            std::stringstream buffer{};
            const size_t max_buffer_size = 0;
            size_t actual_buffer_filling = 0;
            std::vector<std::function<void(std::string)>> callback;
            std::mutex write_mutex{};
        };
    }

    class ATLogger : public interface::ILogger
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
        static void _add_callback(std::function<void(std::string)> callback, inner::LoggerInfo *log_section);
        static void _add_callback(std::function<void(std::string)> callback, std::string log_section);

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
        void log_info(std::string msg) override;
        //log debug to corrent logger
        void log_debug(std::string msg) override;
        //log error to corrent logger
        void log_error(std::string msg) override;
        //log fatal to corrent logger
        void log_fatal(std::string msg, int exit_code) override;

        //flush base logger
        static void b_flush();
        //flush log_section
        static void flush(std::string log_section);
        //flush corrent logger_section
        void flush() override;

        static void b_add_callback(std::function<void(std::string)> callback);
        static void add_callback(std::function<void(std::string)> callback, std::string log_section = "");
        void add_callback(std::function<void(std::string)> callback) override;
        //create base logger section
        static void init_base_logger(size_t buffer_size = 1024, std::string fpath = "./default.log", bool throw_if_exist = true);
        //check existanse log section;
        //if need_create_if_not_exist == true create and return false;
        //if need_create_if_not_exist == false and not exist return false;
        //if need_create_if_not_exist == anything and exist return true
        static bool is_section_exist(std::string log_section = "", bool need_create_if_not_exist = false, std::string fpath = "./default.log", size_t buffer_size = 1024);
        static void create_section(std::string log_section, std::string fpath = "./default.log", size_t buffer_size = 1024, bool throw_if_exist = true);
    };
}

#endif