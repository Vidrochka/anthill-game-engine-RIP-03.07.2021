#ifndef at_logger_strategy
#define at_logger_strategy

#include "ATLoggerEvent.hpp"
#include "../Types/ATString.hpp"
#include "ATLogMsg.hpp"

#include <string>
#include <sstream>
#include <fstream>

using namespace at::type::string;

namespace at::utils::log_system::strategy
{
    namespace at_interface
    {
        class ILogStrategy
        {
        public:
            virtual ~ILogStrategy() {}
            virtual auto log(log_msg::LogMsg log_msg) -> void = 0;
            virtual auto flush() -> void = 0;
        };
    } 
}

#endif //at_logger_strategy
