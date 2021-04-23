#ifndef at_render_provider
#define at_render_provider

#include "../draw-types/ATImage.hpp"
#include "../draw-types/ATRect.hpp"

#include "../../../anthill-game-engine-utils/log-system/ATLogger.hpp"
#include "../../../anthill-game-engine-utils/types/ATColor.hpp"

#include "../../../third-party-libs/SDL2-2.0.14/include/SDL.h"
#include "../../../third-party-libs/json/single_include/nlohmann/json.hpp"

#include <memory>
#include <istream>
#include <fstream>
#include <vector>

using namespace at::core::gui::type::rect;
using namespace at::core::gui::type::image;

using namespace at::utils::log_system::logger::at_interface;

using json = nlohmann::json;

namespace at::core::gui::render
{
    enum class RENDER_PROVIDER_TYPE
    {
        DEFAULT = 0,
        OPENGL,
        VULKAN,
        DX12,
        METAL
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(RENDER_PROVIDER_TYPE, {
        {RENDER_PROVIDER_TYPE::DEFAULT, "default"},
        {RENDER_PROVIDER_TYPE::OPENGL, "opengl"},
        {RENDER_PROVIDER_TYPE::VULKAN, "vulkan"},
        {RENDER_PROVIDER_TYPE::DX12, "directx12"},
        {RENDER_PROVIDER_TYPE::METAL, "metal"},
    })

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
            virtual auto draw_image(std::shared_ptr<Image> image, fui32_rect_at draw_rect, fui32_rect_at texture_rect) -> void = 0;
            virtual auto add_shader(std::ifstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t = 0;
            virtual auto add_shader(u8string_at shader_file_name, SHADER_TYPE shader_type) -> uint_fast32_t = 0;
            virtual auto add_shader(std::stringstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t = 0;
            virtual auto delete_shader(uint_fast32_t shader_id, SHADER_TYPE shader_type) -> void = 0;
            virtual auto add_shaders_program(std::map<SHADER_TYPE, uint_fast32_t> shaders_id_map) -> uint_fast32_t = 0;
            virtual auto delete_shaders_program(uint_fast32_t shader_program_id) -> void = 0;
            virtual auto initialize_render_context(SDL_Window &window) -> void = 0;
            virtual auto select_render_context() -> void = 0;
            virtual auto prepare_new_frame(at::type::color::RGBA_at<uint8_t> color) -> void = 0;
            virtual auto release() -> void;
            virtual auto get_render_type()->RENDER_PROVIDER_TYPE;
        };
    }

    //std::shared_ptr<ILogger> at_interface::IRenderProvider::_logger = nullptr;

}

#endif //at_render_provider