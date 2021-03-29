#ifndef at_logger_manager
#define at_logger_manager

#include "ATLogger.hpp"
#include "ATLoggerContext.hpp"
#include "ATLoggerStrategy.hpp"
#include <map>
#include <mutex>
#include <string>
#include "../Types/ATString.hpp"

using namespace at::utils::logger_manager::logger::interface;
using namespace at::utils::logger_manager::logger;
using namespace at::utils::logger_manager::strategy::interface;
using namespace at::utils::logger_manager::strategy;
using namespace at::type::string;

namespace at::utils::logger_manager
{
    class LoggerManager
    {
    private:
        static std::map<u8string_at, logger_context::LoggerContext *> _logger_context_map;
        static std::mutex *_add_new_section_mutex;

    public:
        static void flush_all();
        static void create_logger(u8string_at log_name, ILogStrategy *strategy = new DefaultFileLogStrategy{}, bool throw_if_exist = true);
        //check existanse log;
        //if need_create_if_not_exist == true create and return false;
        //if need_create_if_not_exist == false and not exist return false;
        //if need_create_if_not_exist == anything and exist return true
        static bool is_logger_exist(u8string_at log_name, bool need_create_if_not_exist = false, ILogStrategy *strategy = new DefaultFileLogStrategy{});
        static ILogger *get_logger(u8string_at log_name);
    };
}

#endif