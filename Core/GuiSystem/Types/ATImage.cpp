#include "ATImage.hpp"
#include "../../../third_party_libs/stb/stb_image.h"

namespace at::core::gui::type::image
{
    Image::Image(u8string_at file_name) {
        _file_name = file_name;
        stbi_set_flip_vertically_on_load(true);
        _data = stbi_load(_file_name.c_str(), &_width, &_height, &_nrChannels, 0); 
    }

    Image::~Image() {
        stbi_image_free(_data);
    }

    auto Image::get_data() -> unsigned char * {
        return _data;
    }

    auto Image::get_width() -> int32_t {
        return _width;
    }

    auto Image::get_height() -> int32_t {
        return _height;
    }

    auto Image::get_nrChannels() -> int32_t {
        return _nrChannels;
    }

    auto Image::get_file_name() -> u8string_at {
        return _file_name;
    }
}