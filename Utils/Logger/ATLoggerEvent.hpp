#ifndef at_logger_event
#define at_logger_event

#include <cstdint>

namespace at::utils::logger_manager
{
    namespace event
    {
        enum EVENT_TYPE : std::uint_fast8_t
        {
            DEBUG = 0,
            INFO = 1,
            WARNING = 2,
            ERROR = 3,
            FATAL = 4,
        };
    }
}

#endif