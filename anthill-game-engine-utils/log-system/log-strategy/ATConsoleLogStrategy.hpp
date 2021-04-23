#ifndef at_console_logger_strategy
#define at_console_logger_strategy

#include "../ATLoggerStrategy.hpp"

namespace at::utils::log_system::strategy
{   
    class ConsoleLogStrategy : public at_interface::ILogStrategy
    {
    private:
        std::stringstream _log_buffer;
        const size_t _buffer_size;
        size_t _actual_buffer_filling = 0;

    public:
        ConsoleLogStrategy(size_t buffer_size = 1024);
        ~ConsoleLogStrategy() override;
        auto log(log_msg::LogMsg log_msg) -> void override;
        auto flush() -> void override;
    };
}

#endif //at_console_logger_strategy