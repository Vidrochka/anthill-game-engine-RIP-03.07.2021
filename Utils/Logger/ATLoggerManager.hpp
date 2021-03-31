#ifndef at_logger_manager
#define at_logger_manager

#include "ATLogger.hpp"
#include "ATLoggerContext.hpp"
#include "ATLoggerStrategy.hpp"
#include <map>
#include <vector>
#include <mutex>
#include <string>
#include "../Types/ATString.hpp"

using namespace at::utils::logger_manager::logger::at_interface;
using namespace at::utils::logger_manager::logger;
using namespace at::utils::logger_manager::strategy::at_interface;
using namespace at::utils::logger_manager::strategy;
using namespace at::type::string;

namespace at::utils::logger_manager
{
    namespace at_interface
    {
        class ILoggerManager
        {
        public:
            virtual ~ILoggerManager() {}
            virtual void flush_all() = 0;
            virtual void create_logger(u8string_at log_name, ILogStrategy *strategy = new DefaultFileLogStrategy{}, bool throw_if_exist = true) = 0;
            //check existanse log;
            //if need_create_if_not_exist == true create and return false;
            //if need_create_if_not_exist == false and not exist return false;
            //if need_create_if_not_exist == anything and exist return true
            virtual bool is_logger_exist(u8string_at log_name, bool need_create_if_not_exist = false, ILogStrategy *strategy = new DefaultFileLogStrategy{}) = 0;
            virtual AbstractLogger *get_logger(u8string_at log_name) = 0;
        };
    }
    class LoggerManager : public at_interface::ILoggerManager
    {
    private:
        std::map<u8string_at, logger_context::LoggerContext *> _logger_context_map;
        std::mutex *_modify_context_collection_mx;
        std::vector<AbstractLogger *> _created_logger_collection;

    public:
        LoggerManager();
        ~LoggerManager() override;
        void flush_all() override;
        void create_logger(u8string_at log_name, ILogStrategy *strategy = new DefaultFileLogStrategy{}, bool throw_if_exist = true) override;
        bool is_logger_exist(u8string_at log_name, bool need_create_if_not_exist = false, ILogStrategy *strategy = new DefaultFileLogStrategy{}) override;
        AbstractLogger *get_logger(u8string_at log_name) override;
    };
}

#endif