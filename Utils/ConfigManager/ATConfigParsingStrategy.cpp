#include "ATConfigParsingStrategy.hpp"
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <iostream>

using namespace at::utils::config_manager::config::interface;
using namespace at::utils::config_manager::config;
using namespace at::utils::config_manager::source::interface;

namespace at::utils::config_manager::parsing_strategy
{
    ISection *fill_section(IConfigSourceInterface *config_source, size_t nesting);

    bool is_section_start(std::wstring str);
    std::wstring get_section_name(std::wstring str);

    size_t start_with_sym_count(std::wstring &str, const std::wstring &chars);

    std::wstring &comment_trim(std::wstring &str);
    std::wstring &trim(std::wstring &str, const std::wstring &chars);

    IConfig *TomlParsingStrategy::get_config(IConfigSourceInterface *config_source)
    {
        std::map<std::wstring, ISection *> sections_map;

        while (config_source->has_next_data())
        {
            std::wstring line = config_source->get_next_line();
            line = trim(comment_trim(line), L" ");

            if (is_section_start(line))
            {
                sections_map[get_section_name(line)] = fill_section(config_source, 1);
            }
            else
            {
                continue;
            }
        }

        return new DefaultConfig(sections_map);
    }

    ISection *fill_section(IConfigSourceInterface *config_source, size_t nesting)
    {
        std::map<std::wstring, std::wstring> filds_map{};
        std::map<std::wstring, ISection *> sections_map{};

        while (config_source->has_next_data())
        {
            std::wstring line = config_source->get_next_line();

            if (line.empty())
                continue;

            if (is_section_start(line))
            {
                size_t tab_count = start_with_sym_count(line, L"\t");

                /* If section lable higer then current nested level, it is new section
                    [LAble1] <- nested level 1 (\t in line start)
                    A = 1
                    B = 2 
                        [Lable2] <- nested level 2 (\t\t in line start)
                        C = 3
                    
                    P.S. "nested level" = count(\t)
                */

                if (tab_count > nesting)
                {
                    sections_map[get_section_name(line)] = fill_section(config_source, nesting + 1);
                    continue;
                }
                else
                {
                    break;
                }
            }

            size_t splitter_pos = line.find_first_of(L"=");

            if (splitter_pos == std::wstring::npos)
            {
                filds_map[trim(line, L" ")] = L"";
            }
            else
            {
                std::wstring key = line.substr(0, splitter_pos);
                std::wstring value = line.substr(splitter_pos + 1);
                filds_map[trim(key, L" ")] = trim(value, L"\" ");
            }
        }

        return new DefaultSection(filds_map, sections_map);
    }

    bool is_section_start(std::wstring str)
    {
        const std::wregex r(L"\\[[a-zA-Z]+\\]");
        return std::regex_match(str, r);
    }

    std::wstring get_section_name(std::wstring str)
    {
        return trim(str, L"[]");
    }

    std::wstring &ltrim(std::wstring &str, const std::wstring &chars)
    {
        size_t pos = str.find_first_not_of(chars);

        if (pos == std::wstring::npos)
            return str;

        str.erase(0, pos);
        return str;
    }

    std::wstring &rtrim(std::wstring &str, const std::wstring &chars)
    {
        size_t pos = str.find_last_not_of(chars);

        if (pos == std::wstring::npos)
            return str;

        str.erase(pos + 1);
        return str;
    }

    size_t start_with_sym_count(std::wstring &str, const std::wstring &chars)
    {
        return str.find_first_not_of(chars);
    }

    std::wstring &comment_trim(std::wstring &str)
    {
        size_t comment_start = str.find_last_of(L"#");

        if (comment_start == std::wstring::npos)
            return str;

        std::wstring before_comment = str.substr(0, comment_start);

        wchar_t sym_before = ' ';
        size_t count_sym = 0;
        for (auto sym : before_comment)
        {
            if (sym == '\"' && sym_before != '\\') // calculate not shielded sym
                count_sym++;
        }

        // check if # in wstring
        if (count_sym % 2 == 1)
            return str; // # is not comment
        else
            return str.erase(0, comment_start); // # comment
    }

    std::wstring &trim(std::wstring &str, const std::wstring &chars)
    {
        return ltrim(rtrim(str, chars), chars);
    }
}