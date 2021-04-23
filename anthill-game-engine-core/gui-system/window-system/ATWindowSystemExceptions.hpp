#ifndef at_window_system_exceptions
#define at_window_system_exceptions

#include "../../../anthill-game-engine-utils/types/ATString.hpp"

#include <string>
#include <exception>


namespace at::core::gui::window_system::exceptions
{
    class sdl_exception : public std::exception {
    public:
        sdl_exception(at::type::string::u8string_at error) : std::exception(error.c_str()) {}
    };

    class window_system_exception : public std::exception {
    public:
        window_system_exception(at::type::string::u8string_at error) : std::exception(error.c_str()) {}
    };
}


#endif //at_window_system_exceptions