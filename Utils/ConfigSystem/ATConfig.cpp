#include "ATConfig.hpp"

using namespace at::type::string;

namespace at::utils::config_system::config
{
    DefaultSection::DefaultSection(std::map<u8string_at, u8string_at> values_map, std::map<u8string_at, at_interface::ISection *> sections_map)
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

    at_interface::ISection *DefaultSection::get_section(u8string_at section_name)
    {
        return _sections_map[section_name];
    }

    u8string_at DefaultSection::to_debug_string()
    {
        u8string_at res_str = "{\n";

        for (auto &&value_pair : _values_map)
        {
            res_str += value_pair.first + " : " + value_pair.second + "\n";
        }

        for (auto &&section_pair : _sections_map)
        {
            res_str += section_pair.first + " :\n" + section_pair.second->to_debug_string() + "\n";
        }

        return res_str + "}";
    }

    DefaultConfig::DefaultConfig(std::map<u8string_at, at_interface::ISection *> sections_map)
    {
        _sections_map = sections_map;
    }

    DefaultConfig::~DefaultConfig()
    {
        for (auto section : _sections_map)
            delete section.second;
    }

    at_interface::ISection *DefaultConfig::get_section(u8string_at section_name)
    {
        return _sections_map[section_name];
    }

    u8string_at DefaultConfig::to_debug_string()
    {
        u8string_at res_str = "{\n";

        for (auto &&section_pair : _sections_map)
        {
            res_str += section_pair.first + " :\n" + section_pair.second->to_debug_string() + "\n";
        }

        return res_str + "}\n";
    }
}