#ifndef at_color
#define at_color
#include <cassert>
#include <type_traits>
#include <limits>
#include <vector>
#include "ATString.hpp"

namespace at::type::color
{
    template <typename component_t>
    class RGB_at
    {
    public:
        component_t r;
        component_t g;
        component_t b;

        RGB_at(component_t r, component_t g, component_t b) {
            static_assert(std::is_integral<component_t>());

            this->r = r;
            this->g = g;
            this->b = b;
        }

        auto to_vector() -> std::vector<component_t> const {
            return std::vector<component_t>{r, g, b};
        }

        auto to_string() -> const at::type::string::u8string_at{
            return "{ r: "u8at + std::to_string(r) 
            + ", g: "u8at + std::to_string(g) 
            + ", b: "u8at + std::to_string(b) 
            + " }"u8at;
        }

        static auto from_vector(std::vector<component_t> vec) -> RGB_at<component_t> {
            assert(vec.size() == 3);
            return RGB_at<component_t>(vec[0], vec[1], vec[2]);
        }

        static auto get_black() -> RGB_at<component_t> {
            return RGB_at(std::numeric_limits<component_t>::min(), std::numeric_limits<component_t>::min(), std::numeric_limits<component_t>::min());
        }

        static auto get_white() -> RGB_at<component_t> {
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

        RGBA_at(component_t r, component_t g, component_t b, component_t a = std::numeric_limits<component_t>::max()) {
            static_assert(std::is_integral<component_t>());

            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        std::vector<component_t> to_vector() const {
            return std::vector<component_t>{r, g, b, a};
        }

        auto to_string() -> const at::type::string::u8string_at{
            return "{ r: "u8at + std::to_string(r) 
            + ", g: "u8at + std::to_string(g) 
            + ", b: "u8at + std::to_string(b) 
            + ", a: "u8at + std::to_string(a)
            +  " }"u8at;
        }

        static auto from_vector(std::vector<component_t> vec) -> RGBA_at<component_t> {
            assert(vec.size() == 4);
            return RGBA_at<component_t>(vec[0], vec[1], vec[2], vec[3]);
        }

        static auto get_black() -> RGBA_at<component_t> {
            return RGBA_at(std::numeric_limits<component_t>::min(), std::numeric_limits<component_t>::min(), std::numeric_limits<component_t>::min());
        }

        static auto get_white() -> RGBA_at<component_t> {
            return RGBA_at(std::numeric_limits<component_t>::max(), std::numeric_limits<component_t>::max(), std::numeric_limits<component_t>::max());
        }
    };
}

#endif