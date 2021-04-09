#ifndef at_logger_exceptions
#define at_logger_exceptions

#include "../Types/ATString.hpp"

#include <string>
#include <exception>


namespace at::utils::log_system::exceptions
{
    class logger_context_already_exist_exception : public std::exception {
    public:  
        logger_context_already_exist_exception(at::type::string::u8string_at error) : std::exception(error.c_str()) {}
    };

    class log_file_unawalable_exception : public std::exception {
    public:  
        log_file_unawalable_exception(at::type::string::u8string_at description, at::type::string::u8string_at file_name) :
         std::exception((description + ":"u8at + file_name).c_str()) {}
    };
}


#endif