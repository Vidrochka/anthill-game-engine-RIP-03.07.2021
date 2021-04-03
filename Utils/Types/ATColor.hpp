#ifndef at_color
#define at_color
#include <cassert>
#include <type_traits>
#include <limits>

namespace at::type::color
{
    template <typename component_t>
    class RGB_at
    {
    public:
        component_t r;
        component_t g;
        component_t b;

        RGB_at(component_t r, component_t g, component_t b)
        {
            static_assert(std::is_integral<component_t>());

            this->r = r;
            this->g = g;
            this->b = b;
        }

        static auto get_black() -> RGB_at<component_t>
        {
            return RGB_at(std::numeric_limits<component_t>::min(), std::numeric_limits<component_t>::min(), std::numeric_limits<component_t>::min());
        }

        static auto get_white() -> RGB_at<component_t>
        {
            return RGB_at(std::numeric_limits<component_t>::max(), std::numeric_limits<component_t>::max(), std::numeric_limits<component_t>::max());
        }
    };

    template <typename component_t>
    class RGBA_at
    {
    public:
        component_t r;
        component_t g;
        component_t b;
        component_t a;

        RGBA_at(component_t r, component_t g, component_t b, component_t a = std::numeric_limits<component_t>::max())
        {
            static_assert(std::is_integral<component_t>());

            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        static auto get_black() -> RGBA_at<component_t>
        {
            return RGBA_at(std::numeric_limits<component_t>::min(), std::numeric_limits<component_t>::min(), std::numeric_limits<component_t>::min());
        }

        static auto get_white() -> RGBA_at<component_t>
        {
            return RGBA_at(std::numeric_limits<component_t>::max(), std::numeric_limits<component_t>::max(), std::numeric_limits<component_t>::max());
        }
    };
}

#endif