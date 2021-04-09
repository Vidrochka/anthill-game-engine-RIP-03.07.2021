#ifndef at_opengl_render_provider
#define at_opengl_render_provider

#include "../ATRenderProvider.hpp"
#include "../../../third_party_libs/SDL2-2.0.14/include/SDL.h"
#include <set>
#include <map>
#include <utility>

namespace at::core::gui::render
{
    class OpenglRenderProvider : public at_interface::IRenderProvider
    {
    private:
        SDL_GLContext _glcontext;
        //SDL_Window *_window;
        std::set<uint_fast32_t> _vertex_shaders_id_collection;
        std::set<uint_fast32_t> _fragment_shaders_id_collection;
        std::set<uint_fast32_t> _shader_programs_id_collection;

        int _width, _height;

        auto _get_shader_set_by_shader_type(SHADER_TYPE shader_type) -> std::set<uint_fast32_t>&;
        auto _get_new_shader_by_shader_type(SHADER_TYPE shader_type) -> int;
        auto _compile_shader_and_get_result(int shader_id, const char* buffer) -> std::pair<bool, u8string_at>;
        auto _add_shader(const char* shader_data, SHADER_TYPE shader_type) -> uint_fast32_t;

    public:
        OpenglRenderProvider(std::shared_ptr<ILogger> logger, SDL_Window *window);
        ~OpenglRenderProvider() override;
        auto draw_rectangle() -> void override;
        auto draw_triangle() -> void override;
        auto draw_circle() -> void override;
        auto draw_text() -> void override;
        auto draw_line() -> void override;
        auto draw_frame() -> void override;
        auto draw_image(std::shared_ptr<type::image::Image> image, uint_fast32_t shader_program_id, Rect<int_fast32_t> rect) -> void override;
        auto add_shader(std::ifstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t override;
        auto add_shader(u8string_at shader_file_name, SHADER_TYPE shader_type) -> uint_fast32_t override;
        auto add_shader(std::stringstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t override;
        auto delete_shader(uint_fast32_t shader_id, SHADER_TYPE shader_type) -> void override;
        auto add_shaders_program(std::map<SHADER_TYPE, uint_fast32_t> shaders_id_map) -> uint_fast32_t override;
        auto delete_shaders_program(uint_fast32_t shader_program_id) -> void override;
        auto initialize_render_context(SDL_Window &window) -> void override;
        auto select_render_context() -> void override;
        auto prepare_new_frame(at::type::color::RGBA_at<uint8_t> color) -> void override;
    };
}

#endif