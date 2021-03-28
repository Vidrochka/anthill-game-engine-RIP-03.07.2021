#ifndef at_logger_strategy
#define at_logger_strategy
#include "ATLoggerEvent.hpp"
#include <string>
#include <sstream>
#include <fstream>

namespace at::utils::logger::strategy
{
    namespace interface
    {
        class ILogStrategy
        {
        public:
            virtual void Log(at::utils::logger::event::EVENT_TYPE event_type, std::wstring msg, std::wstring log_poin = L"") = 0;
            virtual void Flush() = 0;
        };
    }

    class DefaultFileLogStrategy : public interface::ILogStrategy
    {
    private:
        std::wstringstream _log_buffer;
        std::wstring _file_path;
        std::wofstream _file_stream;
        const size_t _buffer_size;
        size_t _actual_buffer_filling = 0;

    public:
        DefaultFileLogStrategy(std::wstring file_path = L"./default.log", size_t buffer_size = 1024);
        ~DefaultFileLogStrategy();
        void Log(at::utils::logger::event::EVENT_TYPE event_type, std::wstring msg, std::wstring log_poin = L"") override;
        void Flush() override;
    };
}

#endif