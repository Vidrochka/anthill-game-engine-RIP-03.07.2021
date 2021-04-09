#ifndef at_rect
#define at_rect

//#include "../../../Utils/Utils.hpp"

//using namespace at::type::string;

namespace at::core::gui::type::rect
{
    template <typename coord_type>
    class Rect{
    public:
        coord_type x, y;
        coord_type width, height;

        Rect(coord_type x, coord_type y, coord_type width, coord_type height)
        : x(x), y(y), width(width), height(height)
        {
            static_assert(std::is_integral<coord_type>());
        }
    };
}

#endif //at_rect