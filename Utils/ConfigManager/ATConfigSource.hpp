#ifndef at_config_source
#define at_config_source

#include <string>
#include <fstream>

namespace at::utils::config_manager::source
{
    namespace interface
    {
        class IConfigSourceInterface
        {
        public:
            virtual std::wstring get_next_line() = 0;
            virtual bool has_next_data() = 0;
            virtual std::wstring get_all_data() = 0;
        };
    }

    class DefaultFileConfigSource : public interface::IConfigSourceInterface
    {
    private:
        std::wstring _next_line;
        std::wifstream _file_stream;
        bool _has_next_line;

    public:
        DefaultFileConfigSource(std::wstring file_path);
        ~DefaultFileConfigSource();

        std::wstring get_next_line() override;
        bool has_next_data() override;
        std::wstring get_all_data() override;
    };
}

#endif