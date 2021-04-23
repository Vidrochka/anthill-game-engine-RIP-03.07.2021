#ifndef at_file_logger_strategy
#define at_file_logger_strategy

#include "../ATLoggerStrategy.hpp"

namespace at::utils::log_system::strategy
{   
    class FileLogStrategy : public at_interface::ILogStrategy
    {
    private:
        std::stringstream _log_buffer;
        u8string_at _file_path;
        std::ofstream _file_stream;
        const size_t _buffer_size;
        size_t _actual_buffer_filling = 0;

    public:
        FileLogStrategy(u8string_at file_path = "./default.log"u8at, size_t buffer_size = 1024);
        ~FileLogStrategy() override;
        auto log(log_msg::LogMsg log_msg) -> void override;
        auto flush() -> void override;
    };
}

#endif //at_file_logger_strategy