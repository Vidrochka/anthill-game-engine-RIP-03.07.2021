#ifndef at_logger_event
#define at_logger_event

#include <cstdint>

namespace at::utils::logger_manager
{
    namespace event
    {
        enum EVENT_TYPE : std::uint_fast8_t
        {
            LOG_DEBUG = 0,
            LOG_INFO = 1,
            LOG_WARNING = 2,
            LOG_ERROR = 3,
            LOG_FATAL = 4,
        };
    }
}

#endif