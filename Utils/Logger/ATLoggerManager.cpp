#include "ATLoggerManager.hpp"

using namespace at::utils::logger_manager::logger::interface;
using namespace at::utils::logger_manager::logger;
using namespace at::utils::logger_manager::strategy::interface;
using namespace at::utils::logger_manager::strategy;

namespace at::utils::logger_manager
{
    std::map<std::wstring, logger_context::LoggerContext *> LoggerManager::_logger_context_map{};
    std::mutex *LoggerManager::_add_new_section_mutex = new std::mutex{};

    void LoggerManager::flush_all()
    {
        for (auto logger_context : _logger_context_map)
        {
            logger_context::LoggerContext *log_info = logger_context.second;

            std::lock_guard<std::mutex> lg(log_info->write_mutex);

            for (auto strategy : log_info->strategy_list)
                strategy->Flush();
        }
    }

    void LoggerManager::create_logger(std::wstring log_name, ILogStrategy *strategy, bool throw_if_exist)
    {
        if (_logger_context_map.count(log_name) > 0)
        {
            if (throw_if_exist)
                throw std::string("Log section already exist");
            else
                return;
        }

        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        _logger_context_map[log_name] = new logger_context::LoggerContext(strategy);
    }

    bool LoggerManager::is_logger_exist(std::wstring log_name, bool need_create_if_not_exist, ILogStrategy *strategy)
    {
        if (_logger_context_map.count(log_name) > 0)
            return true;

        std::lock_guard<std::mutex> lg(*_add_new_section_mutex);

        if (need_create_if_not_exist)
            _logger_context_map[log_name] = new logger_context::LoggerContext(strategy);

        return false;
    }

    ILogger *LoggerManager::get_logger(std::wstring log_name)
    {
        return new DefaultLogger(_logger_context_map[log_name]);
    }
}