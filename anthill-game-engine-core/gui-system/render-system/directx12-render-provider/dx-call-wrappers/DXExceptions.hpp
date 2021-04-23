#ifndef dx_exceptions
#define dx_exceptions

#include <cstdint>
#include <exception>
#include <Utils/Utils.hpp>

namespace at::core::gui::render::directx::exceptions
{
    class directx_exception : public std::exception {
    public:  
        directx_exception(int64_t error_id) : std::exception(("Debug controller exception. HRESULT: ["u8at +int_to_u8_at(error_id) + "]"u8at).c_str()) {}
    };
}

#endif // dx_exceptions