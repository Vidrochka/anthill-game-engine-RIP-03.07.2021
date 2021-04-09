#include "ATWindowManager.hpp"
#include "../../../Defines.hpp"
#include "../Types/ATImage.hpp"


using namespace at::core::window_system::window_context;
using namespace at::core::window_system::window_initialize_settings;
using namespace at::core::window_system::window_initialize_settings::window_open_mode;
using namespace at::core::window_system::preload_window_initialize_settings;
using namespace at::core::window_system::window_manager::result;

#define no_id 0
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

    auto WindowManager::open_preload_window(PreloadWindowInitializeSettings settings) -> WINDOW_CREATE_RESULT
    {
#ifdef DEBUG_CORE
        json settings_json = settings;
        _logger->log_debug("Open preload window with settings: "u8at + settings_json.dump());
#endif


        std::lock_guard<std::mutex> lg(*_modify_window_collection_mx);

        Uint32 flags = 0;

        _logger->log_debug("Создаем окно с дефолтными настройками отображения. Окно предзагрузки"u8at);

        switch (settings.draw_init_mode)
        {
        case RENDER_PROVIDER_TYPE::DEFAULT:
            _logger->log_debug("Создаем окно с дефолтными настройками рендера. Окно предзагрузки"u8at);
            break;
        case RENDER_PROVIDER_TYPE::OPENGL:
            _logger->log_debug("Инициализируем окно рендером opengl. Окно предзагрузки"u8at);
            flags |= SDL_WINDOW_OPENGL;
            break;
        case RENDER_PROVIDER_TYPE::VULKAN:
            _logger->log_debug("Инициализируем окно рендером vulkan. Окно предзагрузки"u8at);
            flags |= SDL_WINDOW_VULKAN;
            break;
        case RENDER_PROVIDER_TYPE::METAL:
            _logger->log_debug("Инициализируем окно рендером metal. Окно предзагрузки"u8at);
            flags |= SDL_WINDOW_METAL;
            break;
        default:
            _logger->log_error("Окно не будет создано. Неопределенный тип рендера. Окно предзагрузки"u8at);
            return WINDOW_CREATE_RESULT::UNKNOWN_RENDER_SYSTEM;
        }

        if (settings.borderless)
        {
            _logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_BORDERLESS));
            flags |= SDL_WINDOW_BORDERLESS;
        }

        if (settings.resizable)
        {
            _logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_RESIZABLE));
            flags |= SDL_WINDOW_RESIZABLE;
        }

        if (settings.grabbed)
        {
            _logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_INPUT_GRABBED));
            flags |= SDL_WINDOW_INPUT_GRABBED;
        }

        if (settings.highdpi)
        {
            _logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_ALLOW_HIGHDPI));
            flags |= SDL_WINDOW_ALLOW_HIGHDPI;
        }

        _logger->log_debug("Общее состояние флагов: "u8at + int_to_u8_at(flags));

        SDL_Window *window = SDL_CreateWindow(
            settings.lable.c_str(),
            settings.x_pos,
            settings.y_pos,
            settings.width,
            settings.height,
            flags | SDL_WINDOW_SHOWN );

        if (window == nullptr)
            _logger->log_error("STD-ERROR: "u8at + SDL_GetError() + "Окно предзагрузки"u8at);

        //SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //if (renderer == nullptr)
            //_logger->log_error("STD-ERROR: "u8at + SDL_GetError() + "Окно предзагрузки"u8at);

        //_logger->log_info("Устанавливаем цвет окна: "u8at + settings.backgroud_color.to_string() + "Окно предзагрузки"u8at);
        //SDL_SetRenderDrawColor(renderer, settings.backgroud_color.r, settings.backgroud_color.g, settings.backgroud_color.b, settings.backgroud_color.a);
        //SDL_RenderClear(renderer);
        //SDL_RenderPresent(renderer);

        _render_provider = at::core::gui::render::get_render_provider(settings.draw_init_mode, std::shared_ptr(_logger), window);

        auto id_v = _render_provider->add_shader("./shader_default.glsl_v"u8at, SHADER_TYPE::VERTEX);
        auto id_f = _render_provider->add_shader("./shader_default.glsl_f"u8at, SHADER_TYPE::FRAGMENT);
        auto prog_id = _render_provider->add_shaders_program({{SHADER_TYPE::VERTEX, id_v}, {SHADER_TYPE::FRAGMENT, id_f}});

        //_logger->log_info("Устанавливаем цвет окна: "u8at + settings.backgroud_color.to_string() + "Окно предзагрузки"u8at);
        _render_provider->prepare_new_frame(settings.backgroud_color);
       
        int width, height;
        SDL_GetWindowSize(window, &width, &height);

        //_logger->log_info("Рисуем картинку: "u8at + settings.picture_path + "Окно предзагрузки"u8at);
        _render_provider->draw_image(at::core::gui::type::image::Image::get_new_image(settings.picture_path), 
            prog_id, Rect<int_fast32_t>{0,0,static_cast<int_fast32_t>(width),static_cast<int_fast32_t>(height)});

        SDL_GL_SwapWindow(window);

        SDL_Delay(3000);

        return WINDOW_CREATE_RESULT::OK;
    }

    auto WindowManager::close_preload_window() -> void
    {
    }

    auto WindowManager::open_new_window(WindowInitializeSettings settings) -> std::pair<WINDOW_CREATE_RESULT,uint16_t>
    {
        uint16_t window_id = _guid_fabric.get_new_id();
        auto str_window_id = int_to_u8_at(window_id);
        _logger->log_debug("Создаем новое окно. Id: "u8at + str_window_id);
        std::lock_guard<std::mutex> lg(*_modify_window_collection_mx);

        Uint32 flags = 0;

        switch (settings.open_mode)
        {
        case WINDOW_OPEN_MODE::DEFAULT:
            _logger->log_debug("Создаем окно с дефолтными настройками отображения. Id окна: "u8at + str_window_id);
            break;
        case WINDOW_OPEN_MODE::FULL_SCREEN:
            _logger->log_debug("Создаем полноэкранное окно. Id окна: "u8at + str_window_id);
            flags |= SDL_WINDOW_FULLSCREEN;
            break;
        case WINDOW_OPEN_MODE::HIDDEN:
            _logger->log_debug("Создаем скрытое окно. Id окна: "u8at + str_window_id);
            flags |= SDL_WINDOW_HIDDEN;
            break;
        case WINDOW_OPEN_MODE::MAXIMIZED:
            _logger->log_debug("Создаем развернутое окно. Id окна: "u8at + str_window_id);
            flags |= SDL_WINDOW_MAXIMIZED;
            break;
        case WINDOW_OPEN_MODE::MINIMIZED:
            _logger->log_debug("Создаем свернутое окно. Id окна: "u8at + str_window_id);
            flags |= SDL_WINDOW_MINIMIZED;
            break;
        default:
            _logger->log_error(u8string_at("Окно не будет создано. Неопределенный тип открытия. Id окна: "u8at) + str_window_id);
            return {WINDOW_CREATE_RESULT::UNKNOWN_OPEN_MODE, no_id};
        }

        switch (settings.draw_init_mode)
        {
        case RENDER_PROVIDER_TYPE::DEFAULT:
            _logger->log_debug(u8string_at("Создаем окно с дефолтными настройками рендера. Id окна: "u8at) + str_window_id);
            break;
        case RENDER_PROVIDER_TYPE::OPENGL:
            _logger->log_debug(u8string_at("Инициализируем окно рендером opengl. Id окна: "u8at) + str_window_id);
            flags |= SDL_WINDOW_OPENGL;
            break;
        case RENDER_PROVIDER_TYPE::VULKAN:
            _logger->log_debug(u8string_at("Инициализируем окно рендером vulkan. Id окна: "u8at) + str_window_id);
            flags |= SDL_WINDOW_VULKAN;
            break;
        case RENDER_PROVIDER_TYPE::METAL:
            _logger->log_debug(u8string_at("Инициализируем окно рендером metal. Id окна: "u8at) + str_window_id);
            flags |= SDL_WINDOW_METAL;
            break;
        default:
            _logger->log_error("Окно не будет создано. Неопределенный тип рендера. Id окна: "u8at + str_window_id);
            return {WINDOW_CREATE_RESULT::UNKNOWN_RENDER_SYSTEM, no_id};
        }

        if (settings.borderless)
        {
            _logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_BORDERLESS));
            flags |= SDL_WINDOW_BORDERLESS;
        }

        if (settings.resizable)
        {
            _logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_RESIZABLE));
            flags |= SDL_WINDOW_RESIZABLE;
        }

        if (settings.grabbed)
        {
            _logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_INPUT_GRABBED));
            flags |= SDL_WINDOW_INPUT_GRABBED;
        }

        if (settings.highdpi)
        {
            _logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_ALLOW_HIGHDPI));
            flags |= SDL_WINDOW_ALLOW_HIGHDPI;
        }

        _logger->log_debug("Общее состояние флагов: "u8at + int_to_u8_at(flags));

        SDL_Window *window = SDL_CreateWindow(
            settings.lable.c_str(),
            settings.x_pos,
            settings.y_pos,
            settings.width,
            settings.height,
            flags | SDL_WINDOW_SHOWN );

        if (window == nullptr)
            _logger->log_error("STD-ERROR: "u8at + SDL_GetError() + "Id окна: "u8at + str_window_id);

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (renderer == nullptr)
            _logger->log_error("STD-ERROR: "u8at + SDL_GetError() + "Id окна: "u8at + str_window_id);

        _window_map[window_id] = new WindowContext(window, renderer);

        auto res = settings.backgroud_color.to_string();
        _logger->log_info("Устанавливаем цвет окна: "u8at + settings.backgroud_color.to_string() + "Id окна: "u8at + str_window_id);
        SDL_SetRenderDrawColor(renderer, settings.backgroud_color.r, settings.backgroud_color.g, settings.backgroud_color.b, settings.backgroud_color.a);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        return {WINDOW_CREATE_RESULT::OK, window_id};
    }
}