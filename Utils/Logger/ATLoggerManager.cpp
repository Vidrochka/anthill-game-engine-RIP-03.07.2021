#include "ATLoggerManager.hpp"
#include <iostream>

using namespace at::utils::logger_manager::logger::at_interface;
using namespace at::utils::logger_manager::logger;
using namespace at::utils::logger_manager::strategy::at_interface;
using namespace at::utils::logger_manager::strategy;
using namespace at::type::string;

namespace at::utils::logger_manager
{
    LoggerManager::LoggerManager()
    {
        _modify_context_collection_mx = new std::mutex();
    }

    LoggerManager::~LoggerManager()
    {
        flush_all();

        for (auto &&i : _logger_context_map)
        {
            bool need_delete = false;
            {
                std::lock_guard<std::mutex> lg(i.second->write_mutex);
                i.second->_owners_counter--;

                if (i.second->_owners_counter == 0)
                    need_delete = true;
            } //можно проще сделать без лок гварда, но я хочу так)

            if (need_delete)
            {
                delete i.second;
                i.second = nullptr;
            }
        }

        delete _modify_context_collection_mx;
    }

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

    void LoggerManager::create_logger(u8string_at log_name, ILogStrategy *strategy, bool throw_if_exist)
    {
        if (_logger_context_map.count(log_name) > 0)
        {
            if (throw_if_exist)
                throw std::string("Log section already exist");
            else
                return;
        }

        std::lock_guard<std::mutex> lg(*_modify_context_collection_mx);

        _logger_context_map[log_name] = new logger_context::LoggerContext(strategy);
    }

    bool LoggerManager::is_logger_exist(u8string_at log_name, bool need_create_if_not_exist, ILogStrategy *strategy)
    {
        if (_logger_context_map.count(log_name) > 0)
            return true;

        std::lock_guard<std::mutex> lg(*_modify_context_collection_mx);

        if (need_create_if_not_exist)
            _logger_context_map[log_name] = new logger_context::LoggerContext(strategy);

        return false;
    }

    AbstractLogger *LoggerManager::get_logger(u8string_at log_name)
    {
        auto context = _logger_context_map[log_name];

        std::lock_guard<std::mutex> lg(context->write_mutex);
        context->_owners_counter++;

        AbstractLogger *logger = new DefaultLogger(context);
        return logger;
    }
}