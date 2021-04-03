#ifndef at_logger_context
#define at_logger_context

#include "ATLoggerStrategy.hpp"
#include <vector>
#include <mutex>

using namespace at::utils::log_system::strategy::at_interface;
using namespace at::utils::log_system::strategy;

namespace at::utils::log_system
{
    namespace logger_context
    {
        struct LoggerContext
        {
        public:
            LoggerContext() {}
            LoggerContext(ILogStrategy *strategy)
                : strategy_list(std::vector{strategy})
            {
            }
            ~LoggerContext()
            {
                for (auto &&strategy : strategy_list)
                {
                    delete strategy;
                }

                strategy_list.clear();
            }
            std::vector<ILogStrategy *> strategy_list;
            std::mutex write_mutex{};
        };
    }
}

#endif