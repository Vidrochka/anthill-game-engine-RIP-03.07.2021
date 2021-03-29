#include "ATConfigSource.hpp"
#include <sstream>

namespace at::utils::config_manager::source
{
    DefaultFileConfigSource::DefaultFileConfigSource(std::wstring file_path)
    {
        _file_stream = std::wifstream(file_path);
        get_next_line();
    }

    DefaultFileConfigSource::~DefaultFileConfigSource()
    {
        _file_stream.close();
    }

    std::wstring DefaultFileConfigSource::get_next_line()
    {
        std::wstring res_line = _next_line;

        // idk how it work. if you know, change to one line like _has_next_line = std::getline()
        if (std::getline(_file_stream, _next_line))
            _has_next_line = true;
        else
            _has_next_line = false;

        return res_line;
    }

    bool DefaultFileConfigSource::has_next_data()
    {
        return _has_next_line;
    }

    std::wstring DefaultFileConfigSource::get_all_data()
    {
        std::streampos read_pos = _file_stream.tellg();

        _file_stream.seekg(0, std::ios::end);
        std::streampos length = _file_stream.tellg();
        wchar_t *buffer = new wchar_t[length];

        _file_stream.seekg(0, std::ios::beg);
        _file_stream.read(buffer, length);

        _file_stream.seekg(0, read_pos);
        return std::wstring(buffer);
    }
}