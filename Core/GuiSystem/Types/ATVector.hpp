#ifndef at_vector
#define at_vector

//#include "../../../Utils/Utils.hpp"

//using namespace at::type::string;

namespace at::core::gui::type::rect
{
    template <typename coord_type>
    class Vecor2D_at{   
    public:
        coord_type x, y;

        Vecor2D_at(coord_type x, coord_type y) 
        : x(x), y(y)
        {
            static_assert(std::is_integral<coord_type>());
        }
    };

    template <typename coord_type>
    class Vecor3D_at{   
    public:
        coord_type x, y, z;

        Vecor3D_at(coord_type x, coord_type y, coord_type z) 
        : x(x), y(y), z(z)
        {
            static_assert(std::is_integral<coord_type>());
        }
    };
}

#endif //at_vector