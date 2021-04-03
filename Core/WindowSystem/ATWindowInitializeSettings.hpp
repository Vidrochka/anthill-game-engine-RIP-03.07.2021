#ifndef at_window_initialize_settings
#define at_window_initialize_settings

#include "../../third_party_libs/SDL2-2.0.14/include/SDL.h"
#include "../../Utils/Utils.hpp"
#include <cstdint>

using namespace at::type::color;

namespace at::core::window_system::window_initialize_settings
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
    }

    namespace window_draw_init_mode
    {
        enum class WINDOW_DRAW_INIT_MODE
        {
            DEFAULT = 0,
            OPENGL,
            VULKAN,
            METAL
        };
    }

    using namespace at::core::window_system::window_initialize_settings::window_open_mode;
    using namespace at::core::window_system::window_initialize_settings::window_draw_init_mode;

    struct WindowInitializeSettings
    {
    public:
        int_least16_t height = 600;
        int_least16_t width = 800;
        int_least16_t x_pos = SDL_WINDOWPOS_CENTERED;
        int_least16_t y_pos = SDL_WINDOWPOS_CENTERED;
        u8string_at lable = "default";
        u8string_at window_name;
        WINDOW_OPEN_MODE open_mode = WINDOW_OPEN_MODE::DEFAULT;
        WINDOW_DRAW_INIT_MODE draw_init_mode = WINDOW_DRAW_INIT_MODE::DEFAULT;
        bool borderless = false;
        bool resizable = true;
        bool grabbed = false;
        bool highdpi = false;
        RGBA_at<uint8_t> backgroud_color = RGBA_at<uint8_t>::get_white();

        WindowInitializeSettings(u8string_at window_name)
        {
            lable = window_name;
            this->window_name = window_name;
        }

        auto set_height(int_least16_t height) -> WindowInitializeSettings *
        {
            this->height = height;
            return this;
        }

        auto set_width(int_least16_t width) -> WindowInitializeSettings *
        {
            this->width = width;
            return this;
        }

        auto set_lable(u8string_at lable) -> WindowInitializeSettings *
        {
            this->lable = lable;
            return this;
        }

        auto set_x_pos(int_least16_t x_pos) -> WindowInitializeSettings *
        {
            this->x_pos = x_pos;
            return this;
        }

        auto set_y_pos(int_least16_t y_pos) -> WindowInitializeSettings *
        {
            this->y_pos = y_pos;
            return this;
        }

        auto set_open_mode(WINDOW_OPEN_MODE open_mode) -> WindowInitializeSettings *
        {
            this->open_mode = open_mode;
            return this;
        }

        auto set_draw_init_mode(WINDOW_DRAW_INIT_MODE draw_init_mode) -> WindowInitializeSettings *
        {
            this->draw_init_mode = draw_init_mode;
            return this;
        }

        auto set_borderless(bool borderless) -> WindowInitializeSettings *
        {
            this->borderless = borderless;
            return this;
        }

        auto set_resizable(bool resizable) -> WindowInitializeSettings *
        {
            this->resizable = resizable;
            return this;
        }

        auto set_grabbed(bool grabbed) -> WindowInitializeSettings *
        {
            this->grabbed = grabbed;
            return this;
        }

        auto set_highdpi(bool highdpi) -> WindowInitializeSettings *
        {
            this->highdpi = highdpi;
            return this;
        }

        auto set_backgroud_color(RGBA_at<uint8_t> backgroud_color) -> WindowInitializeSettings *
        {
            this->backgroud_color = backgroud_color;
            return this;
        }
    };

}

#endif