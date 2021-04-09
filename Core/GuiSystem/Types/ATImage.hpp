#ifndef at_image
#define at_image

#include "../../../Utils/Utils.hpp"
#include <memory>

using namespace at::type::string;

namespace at::core::gui::type::image
{
    class Image
    {
    private:
        Image(const Image&) = delete;
        void Image::operator=( const Image& ) = delete;
        Image(u8string_at file_name);

        int32_t _width, _height, _nrChannels;
        u8string_at _file_name;
        unsigned char * _data;
    public:        
        ~Image();
        auto get_data() -> unsigned char *;
        auto get_width() -> int32_t;
        auto get_height() -> int32_t;
        auto get_nrChannels() -> int32_t;
        auto get_file_name() -> u8string_at;

        static auto get_new_image(u8string_at file_name) -> std::shared_ptr<Image>
        {
            std::shared_ptr<Image> image = std::shared_ptr<Image>(new Image(file_name));
            return image->get_data() == nullptr ? nullptr : image;
        }
    };
}

#endif //at_image