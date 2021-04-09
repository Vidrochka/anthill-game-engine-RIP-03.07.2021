#ifndef at_render_provider
#define at_render_provider

#include "../Types/ATImage.hpp"
#include "../Types/ATRect.hpp"
#include "../../../third_party_libs/SDL2-2.0.14/include/SDL.h"
#include <memory>
#include <istream>
#include <fstream>
#include <vector>

using namespace at::core::gui::type::rect;
using namespace at::core::gui::type::image;

namespace at::core::gui::render
{

    enum class SHADER_TYPE{
        VERTEX = 0,
        FRAGMENT,
    };

    namespace at_interface
    {
        class IRenderProvider
        {
        protected:
            SDL_Window *_window;
            std::shared_ptr<ILogger> _logger;
        public:
            IRenderProvider(std::shared_ptr<ILogger> logger, SDL_Window *window) {
                _logger = logger;
                _window = window;
            }
            virtual ~IRenderProvider() {}
            virtual auto draw_rectangle() -> void = 0;
            virtual auto draw_triangle() -> void = 0;
            virtual auto draw_circle() -> void = 0;
            virtual auto draw_text() -> void = 0;
            virtual auto draw_line() -> void = 0;
            virtual auto draw_frame() -> void = 0;
            virtual auto draw_image(std::shared_ptr<type::image::Image> image, uint_fast32_t shader_program_id, Rect<int_fast32_t> rect) -> void = 0;
            virtual auto add_shader(std::ifstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t = 0;
            virtual auto add_shader(u8string_at shader_file_name, SHADER_TYPE shader_type) -> uint_fast32_t = 0;
            virtual auto add_shader(std::stringstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t = 0;
            virtual auto delete_shader(uint_fast32_t shader_id, SHADER_TYPE shader_type) -> void = 0;
            virtual auto add_shaders_program(std::map<SHADER_TYPE, uint_fast32_t> shaders_id_map) -> uint_fast32_t = 0;
            virtual auto delete_shaders_program(uint_fast32_t shader_program_id) -> void = 0;
            virtual auto initialize_render_context(SDL_Window &window) -> void = 0;
            virtual auto select_render_context() -> void = 0;
            virtual auto prepare_new_frame(at::type::color::RGBA_at<uint8_t> color) -> void = 0;
        };
    }

}

#endif //at_render_provider_builder