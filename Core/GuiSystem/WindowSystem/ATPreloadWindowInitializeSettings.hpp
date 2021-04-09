#ifndef at_preload_window_initialize_settings
#define at_preload_window_initialize_settings

#include "../../../third_party_libs/SDL2-2.0.14/include/SDL.h"
#include "../../../Utils/Utils.hpp"
#include "../RenderSystem/ATRenderProviderBuilder.hpp"
#include "ATWindowInitializeSettings.hpp"
#include <cstdint>

using namespace at::type::color;
    using namespace at::core::gui::render;

namespace at::core::window_system::preload_window_initialize_settings
{
    struct PreloadWindowInitializeSettings
    {
    public:
        uint_least32_t height = 600;
        uint_least32_t width = 800;
        uint_least32_t x_pos = static_cast<uint_least32_t>(SDL_WINDOWPOS_CENTERED);
        uint_least32_t y_pos = static_cast<uint_least32_t>(SDL_WINDOWPOS_CENTERED);
        u8string_at lable = "default";
        RENDER_PROVIDER_TYPE draw_init_mode = RENDER_PROVIDER_TYPE::DEFAULT;
        bool borderless = true;
        bool resizable = false;
        bool grabbed = false;
        bool highdpi = false;
        RGBA_at<uint8_t> backgroud_color = RGBA_at<uint8_t>::get_white();
        u8string_at picture_path;

        PreloadWindowInitializeSettings(){
            picture_path = "./test.jpg";    
        }

        PreloadWindowInitializeSettings(u8string_at picture_path)
        {
            this->picture_path = picture_path;
        }

        auto set_height(uint_least32_t height) -> PreloadWindowInitializeSettings &
        {
            this->height = height;
            return *this;
        }

        auto set_width(uint_least32_t width) -> PreloadWindowInitializeSettings &
        {
            this->width = width;
            return *this;
        }

        auto set_lable(u8string_at lable) -> PreloadWindowInitializeSettings &
        {
            this->lable = lable;
            return *this;
        }

        auto set_x_pos(uint_least32_t x_pos) -> PreloadWindowInitializeSettings &
        {
            this->x_pos = x_pos;
            return *this;
        }

        auto set_y_pos(uint_least32_t y_pos) -> PreloadWindowInitializeSettings &
        {
            this->y_pos = y_pos;
            return *this;
        }

        auto set_draw_init_mode(RENDER_PROVIDER_TYPE draw_init_mode) -> PreloadWindowInitializeSettings &
        {
            this->draw_init_mode = draw_init_mode;
            return *this;
        }

        auto set_borderless(bool borderless) -> PreloadWindowInitializeSettings &
        {
            this->borderless = borderless;
            return *this;
        }

        auto set_resizable(bool resizable) -> PreloadWindowInitializeSettings &
        {
            this->resizable = resizable;
            return *this;
        }

        auto set_grabbed(bool grabbed) -> PreloadWindowInitializeSettings &
        {
            this->grabbed = grabbed;
            return *this;
        }

        auto set_highdpi(bool highdpi) -> PreloadWindowInitializeSettings &
        {
            this->highdpi = highdpi;
            return *this;
        }

        auto set_backgroud_color(RGBA_at<uint8_t> backgroud_color) -> PreloadWindowInitializeSettings &
        {
            this->backgroud_color = backgroud_color;
            return *this;
        }
    };

    void to_json(json &j, const PreloadWindowInitializeSettings &win_init_sett);

    void from_json(const json &j, PreloadWindowInitializeSettings &win_init_sett);
}

#endif