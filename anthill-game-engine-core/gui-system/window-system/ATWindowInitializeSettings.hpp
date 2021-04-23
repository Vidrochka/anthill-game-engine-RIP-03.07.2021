#ifndef at_window_initialize_settings
#define at_window_initialize_settings

#include "../../../anthill-game-engine-utils/types/ATColor.hpp"
#include "../../../third-party-libs/SDL2-2.0.14/include/SDL.h"
#include "../render-system/ATRenderProviderBuilder.hpp"
#include <cstdint>

#include "../../../third-party-libs/json/single_include/nlohmann/json.hpp"
#include "../../../anthill-game-engine-utils//types/ATString.hpp"

using json = nlohmann::json;

using namespace at::type::color;
using namespace at::type::string;

namespace at::core::gui::window_system::window_initialize_settings
{
    namespace window_open_mode
    {
        enum class WINDOW_OPEN_MODE
        {
            DEFAULT = 0,
            FULL_SCREEN,
            HIDDEN,
            MAXIMIZED,
            MINIMIZED,
        };

        NLOHMANN_JSON_SERIALIZE_ENUM (WINDOW_OPEN_MODE, {
            {WINDOW_OPEN_MODE::DEFAULT, "default"},
            {WINDOW_OPEN_MODE::FULL_SCREEN, "full_screen"},
            {WINDOW_OPEN_MODE::HIDDEN, "hidden"},
            {WINDOW_OPEN_MODE::MAXIMIZED, "maximized"},
            {WINDOW_OPEN_MODE::MINIMIZED, "minimized"},
        })
    }

    using namespace at::core::gui::window_system::window_initialize_settings::window_open_mode;
    using namespace at::core::gui::render;

    struct WindowInitializeSettings
    {
    public:
        uint_least32_t height = 600;
        uint_least32_t width = 800;
        uint_least32_t x_pos = static_cast<uint_least32_t>(SDL_WINDOWPOS_CENTERED);
        uint_least32_t y_pos = static_cast<uint_least32_t>(SDL_WINDOWPOS_CENTERED);
        u8string_at lable = "default";
        WINDOW_OPEN_MODE open_mode = WINDOW_OPEN_MODE::DEFAULT;
        RENDER_PROVIDER_TYPE draw_init_mode = RENDER_PROVIDER_TYPE::DEFAULT;
        bool borderless = false;
        bool resizable = true;
        bool grabbed = false;
        bool highdpi = false;
        RGBA_at<uint8_t> backgroud_color = RGBA_at<uint8_t>::get_white();

        WindowInitializeSettings() {
        }

        WindowInitializeSettings(u8string_at window_name) {
            lable = window_name;
        }

        auto set_height(uint_least32_t height) -> WindowInitializeSettings & {
            this->height = height;
            return *this;
        }

        auto set_width(uint_least32_t width) -> WindowInitializeSettings & {
            this->width = width;
            return *this;
        }

        auto set_lable(u8string_at lable) -> WindowInitializeSettings & {
            this->lable = lable;
            return *this;
        }

        auto set_x_pos(uint_least32_t x_pos) -> WindowInitializeSettings & {
            this->x_pos = x_pos;
            return *this;
        }

        auto set_y_pos(uint_least32_t y_pos) -> WindowInitializeSettings & {
            this->y_pos = y_pos;
            return *this;
        }

        auto set_open_mode(WINDOW_OPEN_MODE open_mode) -> WindowInitializeSettings & {
            this->open_mode = open_mode;
            return *this;
        }

        auto set_draw_init_mode(RENDER_PROVIDER_TYPE draw_init_mode) -> WindowInitializeSettings & {
            this->draw_init_mode = draw_init_mode;
            return *this;
        }

        auto set_borderless(bool borderless) -> WindowInitializeSettings & {
            this->borderless = borderless;
            return *this;
        }

        auto set_resizable(bool resizable) -> WindowInitializeSettings & {
            this->resizable = resizable;
            return *this;
        }

        auto set_grabbed(bool grabbed) -> WindowInitializeSettings & {
            this->grabbed = grabbed;
            return *this;
        }

        auto set_highdpi(bool highdpi) -> WindowInitializeSettings & {
            this->highdpi = highdpi;
            return *this;
        }

        auto set_backgroud_color(RGBA_at<uint8_t> backgroud_color) -> WindowInitializeSettings & {
            this->backgroud_color = backgroud_color;
            return *this;
        }
    };

    void to_json(json &j, const WindowInitializeSettings &win_init_sett);

    void from_json(const json &j, WindowInitializeSettings &win_init_sett);
}

#endif