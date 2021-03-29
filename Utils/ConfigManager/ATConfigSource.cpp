#include "ATConfigSource.hpp"
#include <sstream>

using namespace at::type::string;

namespace at::utils::config_manager::source
{
    DefaultFileConfigSource::DefaultFileConfigSource(u32string_at file_path)
    {
        _file_stream = std::ifstream(u32_to_u8_at(file_path));
        get_next_line();
    }

    DefaultFileConfigSource::~DefaultFileConfigSource()
    {
        _file_stream.close();
    }

    u32string_at DefaultFileConfigSource::get_next_line()
    {
        u32string_at res_line = _next_line;

        u8string_at buff{};
        // idk how it work. if you know, change to one line like _has_next_line = std::getline()
        if (std::getline(_file_stream, buff))
            _has_next_line = true;
        else
            _has_next_line = false;

        _next_line = u8_to_u32_at(buff);
        return res_line;
    }

    bool DefaultFileConfigSource::has_next_data()
    {
        return _has_next_line;
    }

    u32string_at DefaultFileConfigSource::get_all_data()
    {
        std::streampos read_pos = _file_stream.tellg();

        _file_stream.seekg(0, std::ios::end);
        std::streampos length = _file_stream.tellg();
        char *buffer = new char[length];

        _file_stream.seekg(0, std::ios::beg);
        _file_stream.read(buffer, length);

        _file_stream.seekg(0, read_pos);
        return u8_to_u32_at(u8string_at(buffer));
    }
}