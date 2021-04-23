#ifndef at_logger_context
#define at_logger_context

#include "ATLoggerStrategy.hpp"

#include <vector>
#include <mutex>
#include <memory>

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
            LoggerContext(std::shared_ptr<ILogStrategy> strategy) : strategy_list(std::vector{strategy}) {
            }
            ~LoggerContext() {}
            std::vector<std::shared_ptr<ILogStrategy>> strategy_list;
            std::mutex write_mutex{};
        };
    }
}

#endif //at_logger_context