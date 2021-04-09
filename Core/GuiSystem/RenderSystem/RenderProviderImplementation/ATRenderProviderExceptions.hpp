#ifndef at_render_provider_exceptions
#define at_render_provider_exceptions

#include <cstdint>
#include <exception>
#include "../../../../Utils/Utils.hpp"
#include "../ATRenderProvider.hpp"

namespace at::core::gui::render::exceptions
{
    class shader_not_exist : public std::exception {
    public:  
        shader_not_exist(int shader_id, SHADER_TYPE shader_type) 
        : std::exception(("Shader not exist. Shader id: ["u8at + int_to_u8_at(shader_id) + "] | Shader type : ["u8at + map_shader_type_to_name(shader_type) + "]"u8at).c_str()) {}
    private:
        auto map_shader_type_to_name(SHADER_TYPE shader_type) -> u8string_at {
            switch(shader_type)
            {
                case SHADER_TYPE::VERTEX:
                    return TO_STRING(SHADER_TYPE::VERTEX);
                case SHADER_TYPE::FRAGMENT:
                    return TO_STRING(SHADER_TYPE::FRAGMENT);
            }
        }
    };

    class shader_program_not_exist : public std::exception {
    public:  
        shader_program_not_exist(int shader_program_id) : std::exception(("Shader program not exist. Program id: ["u8at +int_to_u8_at(shader_program_id) + "]"u8at).c_str()) {}
    };

    class shader_compilation_error : public std::exception {
    public:  
        shader_compilation_error(u8string_at description) : std::exception(description.c_str()) {}
    };

    class shader_program_link_error : public std::exception {
    public:  
        shader_program_link_error(u8string_at description) : std::exception(description.c_str()) {}
    };

    class gl3w_error : public std::exception {
    public:  
        gl3w_error(u8string_at description) : std::exception(description.c_str()) {}
    };
}

#endif //at_render_provider_exceptions