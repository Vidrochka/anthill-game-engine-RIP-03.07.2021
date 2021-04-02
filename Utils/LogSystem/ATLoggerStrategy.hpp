#ifndef at_logger_strategy
#define at_logger_strategy
#include "ATLoggerEvent.hpp"
#include "../Types/ATString.hpp"
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
            virtual void Log(at::utils::log_system::event::EVENT_TYPE event_type, u8string_at msg, u8string_at log_poin = "") = 0;
            virtual void Flush() = 0;
        };
    }

    class DefaultFileLogStrategy : public at_interface::ILogStrategy
    {
    private:
        std::stringstream _log_buffer;
        u8string_at _file_path;
        std::ofstream _file_stream;
        const size_t _buffer_size;
        size_t _actual_buffer_filling = 0;

    public:
        DefaultFileLogStrategy(u8string_at file_path = "./default.log", size_t buffer_size = 1024);
        ~DefaultFileLogStrategy() override;
        void Log(at::utils::log_system::event::EVENT_TYPE event_type, u8string_at msg, u8string_at log_poin = "") override;
        void Flush() override;
    };
}

#endif
