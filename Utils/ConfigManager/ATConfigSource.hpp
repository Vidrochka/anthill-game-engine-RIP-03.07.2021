#ifndef at_config_source
#define at_config_source

#include "../Types/ATString.hpp"
#include <string>
#include <fstream>

using namespace at::type::string;

namespace at::utils::config_manager::source
{
    namespace at_interface
    {
        class IConfigSourceInterface
        {
        public:
            virtual u32string_at get_next_line() = 0;
            virtual bool has_next_data() = 0;
            virtual u32string_at get_all_data() = 0;
        };
    }

    class DefaultFileConfigSource : public at_interface::IConfigSourceInterface
    {
    private:
        u32string_at _next_line;
        std::ifstream _file_stream;
        bool _has_next_line;

    public:
        DefaultFileConfigSource(u32string_at file_path);
        ~DefaultFileConfigSource();

        u32string_at get_next_line() override;
        bool has_next_data() override;
        u32string_at get_all_data() override;
    };
}

#endif