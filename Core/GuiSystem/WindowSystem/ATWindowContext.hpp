#ifndef at_window_context
#define at_window_context

#include "../../../third_party_libs/SDL2-2.0.14/include/SDL.h"

namespace at::core::window_system::window_context
{
    class WindowContext
    {
    private:
        WindowContext();

    public:
        WindowContext(SDL_Window *sdl_window, SDL_Renderer *sdl_renderer)
        {
            this->sdl_window = sdl_window;
            this->sdl_renderer = sdl_renderer;
        }

        ~WindowContext()
        {
            delete sdl_renderer;
            delete sdl_window;
        }

        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
    };

}

#endif