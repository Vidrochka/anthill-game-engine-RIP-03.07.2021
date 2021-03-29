#ifndef at_logger_context
#define at_logger_context

#include "ATLoggerStrategy.hpp"
#include <vector>
#include <mutex>

using namespace at::utils::logger_manager::strategy::interface;
using namespace at::utils::logger_manager::strategy;

namespace at::utils::logger_manager
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
            std::vector<ILogStrategy *> strategy_list;
            std::mutex write_mutex{};
        };
    }
}

#endif