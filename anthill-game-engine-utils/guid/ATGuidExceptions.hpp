#ifndef at_guid_exceptions
#define at_guid_exceptions

#include "../Types/ATString.hpp"

#include <string>
#include <exception>
#include <typeinfo>

namespace at::utils::guid::exceptions
{
    template<typename id_type>
    class guid_overflow : public std::exception {
    public:  
        guid_overflow() : std::exception(("Guid overflow. Chose bigger type ["u8at + typeid(id_type).name() + "]"u8at).c_str()) {}
    };
}


#endif