#include "ATConfig.hpp"

namespace at::utils::config_manager::config
{
    DefaultSection::DefaultSection(std::map<std::wstring, std::wstring> values_map, std::map<std::wstring, interface::ISection *> sections_map)
    {
        _values_map = values_map;
        _sections_map = sections_map;
    }

    DefaultSection::~DefaultSection()
    {
        for (auto section : _sections_map)
            delete section.second;
    }

    std::wstring DefaultSection::get_value(std::wstring key)
    {
        return _values_map[key];
    }

    interface::ISection *DefaultSection::get_section(std::wstring section_name)
    {
        return _sections_map[section_name];
    }

    DefaultConfig::DefaultConfig(std::map<std::wstring, interface::ISection *> sections_map)
    {
        _sections_map = sections_map;
    }

    DefaultConfig::~DefaultConfig()
    {
        for (auto section : _sections_map)
            delete section.second;
    }

    interface::ISection *DefaultConfig::get_section(std::wstring section_name)
    {
        return _sections_map[section_name];
    }
}