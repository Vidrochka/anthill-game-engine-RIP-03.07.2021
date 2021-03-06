#include "ATLoggerManager.hpp"
#include "ATLoggerExceptions.hpp"

#include <iostream>

using namespace at::utils::log_system::logger::at_interface;
using namespace at::utils::log_system::logger;
using namespace at::utils::log_system::strategy::at_interface;
using namespace at::utils::log_system::strategy;
using namespace at::type::string;

namespace at::utils::log_system
{
    LoggerManager::LoggerManager() {
        _modify_context_collection_mx = new std::mutex();
    }

    LoggerManager::~LoggerManager() {
        flush_all();

        delete _modify_context_collection_mx;
    }

    auto LoggerManager::flush_all() -> void {
        for (auto logger_context : _logger_context_map)
        {
            auto log_info = logger_context.second;

            std::lock_guard<std::mutex> lg(log_info->write_mutex);

            for (auto strategy : log_info->strategy_list)
                strategy->flush();
        }
    }

    auto LoggerManager::create_logger(u8string_at log_name, std::shared_ptr<ILogStrategy> strategy, bool throw_if_exist) -> void {
        if (_logger_context_map.count(log_name) > 0)
        {
            if (throw_if_exist)
                throw log_system::exceptions::logger_context_already_exist_exception("Log section already exist"u8at);
            else
                return;
        }

        std::lock_guard<std::mutex> lg(*_modify_context_collection_mx);

        _logger_context_map[log_name] = std::shared_ptr<logger_context::LoggerContext>(new logger_context::LoggerContext(strategy));
    }

    auto LoggerManager::is_logger_exist(u8string_at log_name, bool need_create_if_not_exist, std::shared_ptr<ILogStrategy> strategy) -> bool {
        if (_logger_context_map.count(log_name) > 0)
            return true;

        std::lock_guard<std::mutex> lg(*_modify_context_collection_mx);

        if (need_create_if_not_exist)
            _logger_context_map[log_name] = std::shared_ptr<logger_context::LoggerContext>(new logger_context::LoggerContext(strategy));

        return false;
    }

    auto LoggerManager::get_logger(u8string_at log_name) -> std::shared_ptr<ILogger> {
        auto context = _logger_context_map[log_name];

        std::lock_guard<std::mutex> lg(context->write_mutex);

        ILogger *logger = new DefaultLogger(std::shared_ptr<logger_context::LoggerContext>(context));
        return std::shared_ptr<ILogger>(logger);
    }
}