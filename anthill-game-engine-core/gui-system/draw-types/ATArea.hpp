#ifndef at_area
#define at_area

namespace at::core::gui::type::area
{
    template <typename coord_type>
    class Area {
    public:
        coord_type width, height;

        Area(coord_type width, coord_type height) : width(width), height(height) {
            static_assert(std::is_integral<coord_type>());
        }
    };

    typedef Area<int_fast32_t> fi32_area_at;
    typedef Area<uint_fast32_t> fui32_area_at;
}

#endif //at_area