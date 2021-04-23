#ifndef at_window_context
#define at_window_context

#include "../render-system/ATRenderProvider.hpp"
#include "../widgets/ATWidget.hpp"

#include "../../../third-party-libs/SDL2-2.0.14/include/SDL.h"

#include <memory>
#include <functional>

using namespace at::core::gui::render::at_interface;
using namespace at::core::gui::widgets::at_interface;

namespace at::core::gui::window_system::window_context
{
    class Window
    {
    private:
        Window() = delete;
        Window(Window&) = delete;
        Window& operator=(const Window&) = delete;

        uint16_t _window_id;

    public:
        Window(uint16_t window_id, SDL_Window *sdl_window, std::shared_ptr<IRenderProvider> render_provider, RENDER_PROVIDER_TYPE render_provider_type)
            : _window_id(window_id), sdl_window(sdl_window), render_provider(render_provider){ }

        ~Window() {
            if(render_provider != nullptr)
                render_provider->release();
            if(sdl_window != nullptr)
                SDL_DestroyWindow(sdl_window);
        }

        auto draw() -> void {
            if (gui_tree != nullptr)
            {
                int width, height;
                SDL_GetWindowSize(sdl_window, &width, &height);
                gui_tree->draw(render_provider, fui32_rect_at{ 0, 0, width, height }, fui32_rect_at{ 0, 0, width, height });
            }

            if (callback != nullptr)
                callback();
        }

        auto get_window_id() -> uint16_t { return _window_id; }

        std::shared_ptr<IWidget> gui_tree = nullptr;
        std::shared_ptr<IRenderProvider> render_provider = nullptr;
        SDL_Window *sdl_window = nullptr;
        std::function<void(SDL_Window* sdl_window, fui32_rect_at draw_rect)> callback = nullptr;
    };
}

#endif