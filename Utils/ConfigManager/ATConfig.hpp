#ifndef at_config
#define at_config

#include <string>
#include <map>
#include "../Types/ATString.hpp"

using namespace at::type::string;

namespace at::utils::config_manager::config
{
    namespace interface
    {
        class ISection
        {
        public:
            virtual u8string_at get_value(u8string_at key) = 0;
            virtual ISection *get_section(u8string_at section_name) = 0;
        };

        class IConfig
        {
        public:
            virtual ISection *get_section(u8string_at section_name) = 0;
        };
    }

    class DefaultSection : public interface::ISection
    {
    private:
        std::map<u8string_at, u8string_at> _values_map;
        std::map<u8string_at, interface::ISection *> _sections_map;

    public:
        DefaultSection(std::map<u8string_at, u8string_at> values_map, std::map<u8string_at, interface::ISection *> sections_map);
        ~DefaultSection();

        u8string_at get_value(u8string_at key) override;
        interface::ISection *get_section(u8string_at section_name) override;
    };

    class DefaultConfig : public interface::IConfig
    {
    private:
        std::map<u8string_at, interface::ISection *> _sections_map;

    public:
        DefaultConfig(std::map<u8string_at, interface::ISection *> sections_map);
        ~DefaultConfig();

        interface::ISection *get_section(u8string_at section_name) override;
    };
}

#endif