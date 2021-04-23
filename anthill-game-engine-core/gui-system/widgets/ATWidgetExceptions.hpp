#ifndef at_widget_exceptions
#define at_widget_exceptions

#include "../../../anthill-game-engine-utils/types/ATString.hpp"

#include <string>
#include <exception>


namespace at::core::gui::widgets::exceptions
{
    class widget_serialization_exception : public std::exception {
    public:
        widget_serialization_exception(at::type::string::u8string_at error) : std::exception(error.c_str()) {}
    };

    class widget_deserialization_exception : public std::exception {
    public:
        widget_deserialization_exception(at::type::string::u8string_at error) : std::exception(error.c_str()) {}
    };
}


#endif //at_widget_exceptions