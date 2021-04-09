#ifndef at_logger_manager
#define at_logger_manager

#include "ATLogger.hpp"
#include "ATLoggerContext.hpp"
#include "ATLoggerStrategy.hpp"
#include "../Types/ATString.hpp"
#include <map>
#include <vector>
#include <mutex>
#include <string>
#include <memory>

using namespace at::utils::log_system::logger::at_interface;
using namespace at::utils::log_system::logger;
using namespace at::utils::log_system::strategy::at_interface;
using namespace at::utils::log_system::strategy;
using namespace at::type::string;

namespace at::utils::log_system
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
            virtual std::shared_ptr<ILogger> get_logger(u8string_at log_name) = 0;
        };
    }
    class LoggerManager : public at_interface::ILoggerManager
    {
    private:
        std::map<u8string_at, std::shared_ptr<logger_context::LoggerContext>> _logger_context_map;
        std::mutex *_modify_context_collection_mx;

    public:
        LoggerManager();
        ~LoggerManager() override;
        void flush_all() override;
        void create_logger(u8string_at log_name, ILogStrategy *strategy = new DefaultFileLogStrategy{}, bool throw_if_exist = true) override;
        bool is_logger_exist(u8string_at log_name, bool need_create_if_not_exist = false, ILogStrategy *strategy = new DefaultFileLogStrategy{}) override;
        std::shared_ptr<ILogger> get_logger(u8string_at log_name) override;
    };
}

#endif