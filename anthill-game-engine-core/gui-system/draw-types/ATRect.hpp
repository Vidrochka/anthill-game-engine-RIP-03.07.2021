#ifndef at_rect
#define at_rect

#include <cstdint>

namespace at::core::gui::type::rect
{
    template <typename coord_type>
    class Rect{
    public:
        coord_type x, y;
        coord_type width, height;

        Rect(coord_type x, coord_type y, coord_type width, coord_type height) : x(x), y(y), width(width), height(height) {
            static_assert(std::is_integral<coord_type>());
        }

        auto is_include(Rect<coord_type> rect) -> bool {
            if (rect.x >= x && rect.y <= y && (rect.x + rect.width) <= (x + width) && (rect.y + rect.height) <= (y + height))
                return true;

            return false;
        }
    };

    typedef Rect<int_fast32_t> fi32_rect_at;
    typedef Rect<uint_fast32_t> fui32_rect_at;
}

#endif //at_rect