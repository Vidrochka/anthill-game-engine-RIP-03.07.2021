#ifndef at_config
#define at_config

#include <string>
#include <map>

namespace at::utils::config_manager::config
{
    namespace interface
    {
        class ISection
        {
        public:
            virtual std::wstring get_value(std::wstring key) = 0;
            virtual ISection *get_section(std::wstring section_name) = 0;
        };

        class IConfig
        {
        public:
            virtual ISection *get_section(std::wstring section_name) = 0;
        };
    }

    class DefaultSection : public interface::ISection
    {
    private:
        std::map<std::wstring, std::wstring> _values_map;
        std::map<std::wstring, interface::ISection *> _sections_map;

    public:
        DefaultSection(std::map<std::wstring, std::wstring> values_map, std::map<std::wstring, interface::ISection *> sections_map);
        ~DefaultSection();

        std::wstring get_value(std::wstring key) override;
        interface::ISection *get_section(std::wstring section_name) override;
    };

    class DefaultConfig : public interface::IConfig
    {
    private:
        std::map<std::wstring, interface::ISection *> _sections_map;

    public:
        DefaultConfig(std::map<std::wstring, interface::ISection *> sections_map);
        ~DefaultConfig();

        interface::ISection *get_section(std::wstring section_name) override;
    };
}

#endif