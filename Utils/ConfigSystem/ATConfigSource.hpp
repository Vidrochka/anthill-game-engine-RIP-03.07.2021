#ifndef at_config_source
#define at_config_source

#include <string>
#include <fstream>
#include "../Types/ATString.hpp"

using namespace at::type::string;

namespace at::utils::config_system::source
{
    namespace at_interface
    {
        class IConfigSourceInterface
        {
        public:
            virtual ~IConfigSourceInterface(){};
            virtual u32string_at get_line() = 0;
            virtual bool move_to_next_line() = 0;
            virtual u32string_at get_all_data() = 0;
            virtual void reset() = 0;
        };
    }

    class DefaultFileConfigSource : public at_interface::IConfigSourceInterface
    {
    private:
        u32string_at _line;
        std::ifstream _file_stream;

    public:
        DefaultFileConfigSource(u8string_at file_path);
        ~DefaultFileConfigSource() override;

        u32string_at get_line() override;
        bool move_to_next_line() override;
        u32string_at get_all_data() override;
        void reset() override;
    };
}

#endif
