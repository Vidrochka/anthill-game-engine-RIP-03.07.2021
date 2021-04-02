#include "ATConfigSource.hpp"
#include <sstream>
#include <iostream>

using namespace at::type::string;

namespace at::utils::config_system::source
{
    DefaultFileConfigSource::DefaultFileConfigSource(u8string_at file_path)
    {
        _file_stream = std::ifstream(file_path);
    }

    DefaultFileConfigSource::~DefaultFileConfigSource()
    {
        _file_stream.close();
    }

    u32string_at DefaultFileConfigSource::get_line()
    {
        return _line;
    }

    bool DefaultFileConfigSource::move_to_next_line()
    {
        bool has_next_line;

        u8string_at buff{};
        // idk how it work. if you know, change to one line like _has_next_line = std::getline()
        if (std::getline(_file_stream, buff))
            has_next_line = true;
        else
            has_next_line = false;

        _line = u8_to_u32_at(buff);
        return has_next_line;
    }

    u32string_at DefaultFileConfigSource::get_all_data()
    {
        std::streampos read_pos = _file_stream.tellg();

        _file_stream.seekg(0, std::ios::end);
        std::streampos length = _file_stream.tellg();
        char *buffer = new char[length];

        _file_stream.seekg(0, std::ios::beg);
        _file_stream.read(buffer, length);

#pragma warning(suppress : 4244)
        _file_stream.seekg(0, read_pos);
        return u8_to_u32_at(u8string_at(buffer));
    }

    void DefaultFileConfigSource::reset()
    {
        _file_stream.seekg(0, std::ios::beg);
    }
}