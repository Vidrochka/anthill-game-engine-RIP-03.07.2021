#include "ATWindowManager.hpp"

using namespace at::core::window_system::window_context;
using namespace at::core::window_system::window_initialize_settings;
using namespace at::core::window_system::window_initialize_settings::window_open_mode;
using namespace at::core::window_system::window_initialize_settings::window_draw_init_mode;
using namespace at::core::window_system::preload_window_initialize_settings;
using namespace at::core::window_system::window_manager::result;

namespace at::core::window_system::window_manager
{

    WindowManager::WindowManager(std::shared_ptr<ILogger> logger)
    {
        _logger = logger;

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            _logger->log_error(u8string_at{"STD-ERROR: "} + SDL_GetError());

        _modify_window_collection_mx = new std::mutex();
    }

    WindowManager::~WindowManager()
    {
        SDL_Quit();
        delete _modify_window_collection_mx;

        for (auto &window : _window_map)
        {
            SDL_DestroyWindow(window.second->sdl_window);
        }
    }

    auto WindowManager::open_preload_window(PreloadWindowInitializeSettings settings) -> PRELOAD_WINDOW_CREATE_RESULT
    {
        return PRELOAD_WINDOW_CREATE_RESULT::OK;
    }

    auto WindowManager::close_preload_window(u8string_at window_name) -> void
    {
    }

    auto WindowManager::open_new_window(WindowInitializeSettings settings) -> WINDOW_CREATE_RESULT
    {
        _logger->log_debug(u8string_at("Создаем новое окно. Название: ") + settings.window_name);
        std::lock_guard<std::mutex> lg(*_modify_window_collection_mx);

        if (_window_map.count(settings.window_name) > 0)
            return WINDOW_CREATE_RESULT::WINDOW_ALREADY_EXIST;

        Uint32 flags = 0;

        switch (settings.open_mode)
        {
        case WINDOW_OPEN_MODE::DEFAULT:
            _logger->log_debug(u8string_at("Создаем окно с дефолтными настройками отображения. Название: ") + settings.window_name);
            break;
        case WINDOW_OPEN_MODE::FULL_SCREEN:
            _logger->log_debug(u8string_at("Создаем полноэкранное окно. Название: ") + settings.window_name);
            flags |= SDL_WINDOW_FULLSCREEN;
            break;
        case WINDOW_OPEN_MODE::HIDDEN:
            _logger->log_debug(u8string_at("Создаем скрытое окно. Название: ") + settings.window_name);
            flags |= SDL_WINDOW_HIDDEN;
            break;
        case WINDOW_OPEN_MODE::MAXIMIZED:
            _logger->log_debug(u8string_at("Создаем развернутое окно. Название: ") + settings.window_name);
            flags |= SDL_WINDOW_MAXIMIZED;
            break;
        case WINDOW_OPEN_MODE::MINIMIZED:
            _logger->log_debug(u8string_at("Создаем свернутое окно. Название: ") + settings.window_name);
            flags |= SDL_WINDOW_MINIMIZED;
            break;
        default:
            _logger->log_error(u8string_at("Окно не будет создано. Неопределенный тип открытия. Название: ") + settings.window_name);
            return WINDOW_CREATE_RESULT::UNKNOWN_OPEN_MODE;
        }

        switch (settings.draw_init_mode)
        {
        case WINDOW_DRAW_INIT_MODE::DEFAULT:
            _logger->log_debug(u8string_at("Создаем окно с дефолтными настройками рендера. Название: ") + settings.window_name);
            break;
        case WINDOW_DRAW_INIT_MODE::OPENGL:
            _logger->log_debug(u8string_at("Инициализируем окно рендером opengl. Название: ") + settings.window_name);
            flags |= SDL_WINDOW_OPENGL;
            break;
        case WINDOW_DRAW_INIT_MODE::VULKAN:
            _logger->log_debug(u8string_at("Инициализируем окно рендером vulkan. Название: ") + settings.window_name);
            flags |= SDL_WINDOW_VULKAN;
            break;
        case WINDOW_DRAW_INIT_MODE::METAL:
            _logger->log_debug(u8string_at("Инициализируем окно рендером metal. Название: ") + settings.window_name);
            flags |= SDL_WINDOW_METAL;
            break;
        default:
            _logger->log_error(u8string_at("Окно не будет создано. Неопределенный тип рендера. Название: ") + settings.window_name);
            return WINDOW_CREATE_RESULT::UNKNOWN_RENDER_SYSTEM;
        }

        if (settings.borderless)
        {
            _logger->log_debug(u8string_at("Добавляем флаг: ") + TO_STRING(SDL_WINDOW_BORDERLESS));
            flags |= SDL_WINDOW_BORDERLESS;
        }

        if (settings.resizable)
        {
            _logger->log_debug(u8string_at("Добавляем флаг: ") + TO_STRING(SDL_WINDOW_RESIZABLE));
            flags |= SDL_WINDOW_RESIZABLE;
        }

        if (settings.grabbed)
        {
            _logger->log_debug(u8string_at("Добавляем флаг: ") + TO_STRING(SDL_WINDOW_INPUT_GRABBED));
            flags |= SDL_WINDOW_INPUT_GRABBED;
        }

        if (settings.highdpi)
        {
            _logger->log_debug(u8string_at("Добавляем флаг: ") + TO_STRING(SDL_WINDOW_ALLOW_HIGHDPI));
            flags |= SDL_WINDOW_ALLOW_HIGHDPI;
        }

        _logger->log_debug(u8string_at("Общее состояние флагов: " + int_to_u8_at(flags)));

        SDL_Window *window = SDL_CreateWindow(
            settings.lable.c_str(),
            settings.x_pos,
            settings.y_pos,
            settings.width,
            settings.height,
            flags);

        if (window == nullptr)
            _logger->log_error(u8string_at{"STD-ERROR: "} + SDL_GetError());

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

        if (renderer == nullptr)
            _logger->log_error(u8string_at{"STD-ERROR: "} + SDL_GetError());

        _window_map[settings.window_name] = new WindowContext(window, renderer);

        _logger->log_info(u8string_at("Устанавливаем цвет окна r:") + int_to_u8_at(settings.backgroud_color.r) //
                          + " g: " + int_to_u8_at(settings.backgroud_color.g) + " b: " + int_to_u8_at(settings.backgroud_color.b) + " Название: " + settings.window_name);
        SDL_SetRenderDrawColor(renderer, settings.backgroud_color.r, settings.backgroud_color.g, settings.backgroud_color.b, settings.backgroud_color.a);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        return WINDOW_CREATE_RESULT::OK;
    }
}