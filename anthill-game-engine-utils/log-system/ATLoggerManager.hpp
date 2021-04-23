#ifndef at_logger_manager
#define at_logger_manager

#include "ATLogger.hpp"
#include "ATLoggerContext.hpp"
#include "ATLoggerStrategy.hpp"
#include "log-strategy/ATFileLogStrategy.hpp"
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
            virtual auto flush_all() -> void = 0;
            virtual auto create_logger(u8string_at log_name, std::shared_ptr<ILogStrategy> strategy = std::shared_ptr<ILogStrategy>(new FileLogStrategy{}), bool throw_if_exist = true) -> void = 0;
            //check existanse log;
            //if need_create_if_not_exist == true create and return false;
            //if need_create_if_not_exist == false and not exist return false;
            //if need_create_if_not_exist == anything and exist return true
            virtual auto is_logger_exist(u8string_at log_name, bool need_create_if_not_exist = false, std::shared_ptr<ILogStrategy> strategy = std::shared_ptr<ILogStrategy>(new FileLogStrategy{})) -> bool = 0;
            virtual auto get_logger(u8string_at log_name) -> std::shared_ptr<ILogger> = 0;
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
        auto flush_all() -> void override;
        auto create_logger(u8string_at log_name, std::shared_ptr<ILogStrategy> strategy = std::shared_ptr<ILogStrategy>(new FileLogStrategy{}), bool throw_if_exist = true) -> void override;
        auto is_logger_exist(u8string_at log_name, bool need_create_if_not_exist = false, std::shared_ptr<ILogStrategy> strategy = std::shared_ptr<ILogStrategy>(new FileLogStrategy{})) -> bool override;
        auto get_logger(u8string_at log_name) -> std::shared_ptr<ILogger> override;
    };
}

#endif //at_logger_manager