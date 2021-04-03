#ifndef at_preload_window_initialize_settings
#define at_preload_window_initialize_settings

#include "../../third_party_libs/SDL2-2.0.14/include/SDL.h"
#include "../../Utils/Utils.hpp"
#include "ATWindowInitializeSettings.hpp"
#include <cstdint>

using namespace at::type::color;

namespace at::core::window_system::preload_window_initialize_settings
{
    using namespace at::core::window_system::window_initialize_settings::window_draw_init_mode;

    struct PreloadWindowInitializeSettings
    {
    public:
        int_least16_t height = 600;
        int_least16_t width = 800;
        int_least16_t x_pos = SDL_WINDOWPOS_UNDEFINED;
        int_least16_t y_pos = SDL_WINDOWPOS_UNDEFINED;
        u8string_at lable = "default";
        u8string_at window_name;
        WINDOW_DRAW_INIT_MODE draw_init_mode = WINDOW_DRAW_INIT_MODE::DEFAULT;
        bool borderless = false;
        bool resizable = true;
        bool grabbed = false;
        bool highdpi = false;
        RGBA_at<uint8_t> backgroud_color = RGBA_at<uint8_t>::get_white();

        PreloadWindowInitializeSettings(u8string_at window_name)
        {
            lable = window_name;
            this->window_name = window_name;
        }

        auto set_height(int_least16_t height) -> PreloadWindowInitializeSettings *
        {
            this->height = height;
            return this;
        }

        auto set_width(int_least16_t width) -> PreloadWindowInitializeSettings *
        {
            this->width = width;
            return this;
        }

        auto set_lable(u8string_at lable) -> PreloadWindowInitializeSettings *
        {
            this->lable = lable;
            return this;
        }

        auto set_x_pos(int_least16_t x_pos) -> PreloadWindowInitializeSettings *
        {
            this->x_pos = x_pos;
            return this;
        }

        auto set_y_pos(int_least16_t y_pos) -> PreloadWindowInitializeSettings *
        {
            this->y_pos = y_pos;
            return this;
        }

        auto set_draw_init_mode(WINDOW_DRAW_INIT_MODE draw_init_mode) -> PreloadWindowInitializeSettings *
        {
            this->draw_init_mode = draw_init_mode;
            return this;
        }

        auto set_borderless(bool borderless) -> PreloadWindowInitializeSettings *
        {
            this->borderless = borderless;
            return this;
        }

        auto set_resizable(bool resizable) -> PreloadWindowInitializeSettings *
        {
            this->resizable = resizable;
            return this;
        }

        auto set_grabbed(bool grabbed) -> PreloadWindowInitializeSettings *
        {
            this->grabbed = grabbed;
            return this;
        }

        auto set_highdpi(bool highdpi) -> PreloadWindowInitializeSettings *
        {
            this->highdpi = highdpi;
            return this;
        }

        auto set_backgroud_color(RGBA_at<uint8_t> backgroud_color) -> PreloadWindowInitializeSettings *
        {
            this->backgroud_color = backgroud_color;
            return this;
        }
    };

}

#endif