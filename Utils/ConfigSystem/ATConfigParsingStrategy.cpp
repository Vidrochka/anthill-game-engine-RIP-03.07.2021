#include "ATConfigParsingStrategy.hpp"
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <iostream>

using namespace at::utils::config_system::config::at_interface;
using namespace at::utils::config_system::config;
using namespace at::utils::config_system::source::at_interface;
using namespace at::type::string;

namespace at::utils::config_system::parsing_strategy
{
    ISection *fill_section(IConfigSourceInterface *config_source, size_t nesting);

    bool is_section_start(u32string_at str);
    u32string_at get_section_name(u32string_at str);

    size_t start_with_sym_count(u32string_at &str, const u32string_at &chars);

    u32string_at comment_trim(u32string_at str);
    u32string_at trim(u32string_at str, const u32string_at &chars);

    IConfig *TomlParsingStrategy::get_config(IConfigSourceInterface *config_source)
    {
        std::map<u8string_at, ISection *> sections_map;

        config_source->move_to_next_line();
        while (true)
        {
            u32string_at line = trim(comment_trim(config_source->get_line()), U" ");

            if (is_section_start(line))
            {
                sections_map[u32_to_u8_at(get_section_name(line))] = fill_section(config_source, 0);
            }
            else
            {
                if (!config_source->move_to_next_line())
                    break;

                continue;
            }
        }

        return new DefaultConfig(sections_map);
    }

    ISection *fill_section(IConfigSourceInterface *config_source, size_t nesting)
    {
        std::map<u8string_at, u8string_at> filds_map{};
        std::map<u8string_at, ISection *> sections_map{};

        while (config_source->move_to_next_line())
        {
            u32string_at line = trim(comment_trim(config_source->get_line()), U" ");

            if (line.empty())
                continue;

            if (is_section_start(trim(line, U"\t")))
            {
                size_t tab_count = start_with_sym_count(line, U"\t");

                /********************************************************************
                 If section lable higer then current nested level, it is new section
                    [LAble1] <- nested level 1 (\t in line start)
                    A = 1
                    B = 2 
                        [Lable2] <- nested level 2 (\t\t in line start)
                        C = 3
                    
                    P.S. "nested level" = count(\t)                                 
                ********************************************************************/

                if (tab_count > nesting)
                {
                    sections_map[u32_to_u8_at(get_section_name(trim(line, U"\t")))] = fill_section(config_source, nesting + 1);
                    continue;
                }
                else
                {
                    break;
                }
            }

            size_t splitter_pos = line.find_first_of(U"=");

            if (splitter_pos == u32string_at::npos)
            {
                filds_map[u32_to_u8_at(trim(line, U" \t"))] = u8string_at{""};
            }
            else
            {
                u32string_at key = line.substr(0, splitter_pos);
                u32string_at value = line.substr(splitter_pos + 1);
                filds_map[u32_to_u8_at(trim(key, U" \t"))] = u32_to_u8_at(trim(value, U"\" \t"));
            }
        }

        return new DefaultSection(filds_map, sections_map);
    }

    bool is_section_start(u32string_at str)
    {
        const std::regex r("\\[[a-zA-Z0-9]+\\]");
        return std::regex_match(u32_to_u8_at(str), r);
    }

    u32string_at get_section_name(u32string_at str)
    {
        return trim(str, U"[]");
    }

    u32string_at ltrim(u32string_at str, const u32string_at &chars)
    {
        size_t pos = str.find_first_not_of(chars);

        if (pos == u32string_at::npos)
            return str;

        str.erase(0, pos);
        return str;
    }

    u32string_at rtrim(u32string_at str, const u32string_at &chars)
    {
        size_t pos = str.find_last_not_of(chars);

        if (pos == u32string_at::npos)
            return str;

        str.erase(pos + 1);
        return str;
    }

    size_t start_with_sym_count(u32string_at &str, const u32string_at &chars)
    {
        return str.find_first_not_of(chars);
    }

    u32string_at comment_trim(u32string_at str)
    {
        size_t comment_start = str.find_last_of(U"#");

        if (comment_start == u32string_at::npos)
            return str;

        u32string_at before_comment = str.substr(0, comment_start);

        char32_t sym_before = U' ';
        size_t count_sym = 0;
        for (auto sym : before_comment)
        {
            if (sym == U'\"' && sym_before != U'\\') // calculate not shielded sym
                count_sym++;
        }

        // check if # in wstring
        if (count_sym % 2 == 1)
            return str; // # is not comment
        else
            return str.erase(0, comment_start); // # comment
    }

    u32string_at trim(u32string_at str, const u32string_at &chars)
    {
        return ltrim(rtrim(str, chars), chars);
    }
}