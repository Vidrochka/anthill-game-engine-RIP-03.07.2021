#include "ATConfig.hpp"

using namespace at::type::string;

namespace at::utils::config_manager::config
{
    DefaultSection::DefaultSection(std::map<u8string_at, u8string_at> values_map, std::map<u8string_at, interface::ISection *> sections_map)
    {
        _values_map = values_map;
        _sections_map = sections_map;
    }

    DefaultSection::~DefaultSection()
    {
        for (auto section : _sections_map)
            delete section.second;
    }

    u8string_at DefaultSection::get_value(u8string_at key)
    {
        return _values_map[key];
    }

    interface::ISection *DefaultSection::get_section(u8string_at section_name)
    {
        return _sections_map[section_name];
    }

    DefaultConfig::DefaultConfig(std::map<u8string_at, interface::ISection *> sections_map)
    {
        _sections_map = sections_map;
    }

    DefaultConfig::~DefaultConfig()
    {
        for (auto section : _sections_map)
            delete section.second;
    }

    interface::ISection *DefaultConfig::get_section(u8string_at section_name)
    {
        return _sections_map[section_name];
    }
}