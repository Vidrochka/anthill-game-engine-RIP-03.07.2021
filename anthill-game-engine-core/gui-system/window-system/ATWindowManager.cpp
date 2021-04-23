#include "ATWindowManager.hpp"
//#include <Types/ATImage.hpp>
#include "ATWindowSystemExceptions.hpp"

#include "../widgets/ATFrameWidget.hpp"

#include "../../../anthill-game-engine-utils/log-system/log-strategy/ATFileLogStrategy.hpp"
#include "../../../anthill-game-engine-utils/log-system/log-strategy/ATConsoleLogStrategy.hpp"

using namespace at::core::gui::window_system::window_initialize_settings;
using namespace at::core::gui::window_system::window_initialize_settings::window_open_mode;
using namespace at::core::gui::window_system::window_manager::result;
using namespace at::core::gui::widgets;

namespace at::core::gui::window_system::window_manager
{

    WindowManager::WindowManager(std::shared_ptr<ILoggerManager> logger_manager, config::WindowSystemConfig config)
    {
        _config = config;

        _logger_manager = logger_manager;
        _logger_manager->create_logger("window_system_logger", std::shared_ptr<ILogStrategy>(new FileLogStrategy(_config.log_file_name, 0)));
        _window_system_logger = _logger_manager->get_logger("window_system_logger");
        _window_system_logger->add_strategy(std::shared_ptr<ILogStrategy>(new ConsoleLogStrategy(0)));
        _window_system_logger->log_info("Window system logger created");

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            _window_system_logger->log_error(U8StringBuilder{"sdl-error:{0}"u8at}.fmt(0, SDL_GetError()));

        _modify_window_collection_mx = new std::mutex();
    }

    WindowManager::~WindowManager()
    {
        SDL_Quit();
        delete _modify_window_collection_mx;

        /*for (auto &window : _window_map) {
            SDL_DestroyWindow(window.second->sdl_window);
        }*/
    }

    auto WindowManager::process_events() -> void {
        SDL_Event evt;
        while (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
            case SDL_KEYDOWN:
                // Завершаемся при нажатии Esc...
                if (evt.key.keysym.sym == SDLK_ESCAPE)
                    has_close_signal = true;
                break;
            case SDL_QUIT:
                // ... или при закрытии окна
                has_close_signal = true;
                break;
            default:
                SDL_PumpEvents();
                break;
            }
        }
    }

    auto WindowManager::open_new_window(WindowInitializeSettings settings, std::shared_ptr<IWidget> top_widget) -> std::shared_ptr<Window>
    {
#ifdef DEBUG_CORE
        json settings_json = settings;
        _logger->log_debug("Open new window with settings: "u8at + settings_json.dump());
#endif

        uint16_t window_id = _window_id_fabric.get_new_id();
        _window_system_logger->log_debug(U8StringBuilder{ "Создаем новое окно. Id: [{0}]. Высота: [{1}]. Ширина: [{2}]"u8at }
            .fmt(0, window_id)
            .fmt(1,settings.height)
            .fmt(2, settings.width));
        std::lock_guard<std::mutex> lg(*_modify_window_collection_mx);

        Uint32 flags = 0;

        switch (settings.open_mode)
        {
        case WINDOW_OPEN_MODE::DEFAULT:
            _window_system_logger->log_debug(U8StringBuilder{"Создаем окно с дефолтными настройками отображения. Id окна: {0}"u8at}.fmt(0, window_id));
            break;
        case WINDOW_OPEN_MODE::FULL_SCREEN:
            _window_system_logger->log_debug(U8StringBuilder{ "Создаем полноэкранное окно. Id окна: {0}"u8at }.fmt(0, window_id));
            flags |= SDL_WINDOW_FULLSCREEN;
            break;
        case WINDOW_OPEN_MODE::HIDDEN:
            _window_system_logger->log_debug(U8StringBuilder{ "Создаем скрытое окно. Id окна: {0}"u8at }.fmt(0, window_id));
            flags |= SDL_WINDOW_HIDDEN;
            break;
        case WINDOW_OPEN_MODE::MAXIMIZED:
            _window_system_logger->log_debug(U8StringBuilder{ "Создаем развернутое окно. Id окна: {0}"u8at }.fmt(0, window_id));
            flags |= SDL_WINDOW_MAXIMIZED;
            break;
        case WINDOW_OPEN_MODE::MINIMIZED:
            _window_system_logger->log_debug(U8StringBuilder{ "Создаем свернутое окно. Id окна: {0}"u8at }.fmt(0, window_id));
            flags |= SDL_WINDOW_MINIMIZED;
            break;
        default:
            _window_system_logger->log_error(U8StringBuilder{ "Окно не будет создано. Неопределенный тип открытия. Id окна: {0}"u8at }.fmt(0, window_id));
            throw new exceptions::window_system_exception(U8StringBuilder{ "Неопределенный тип открытия [{0}]"u8at }.fmt(0, (int)settings.open_mode));
        }

        switch (settings.draw_init_mode)
        {
        case RENDER_PROVIDER_TYPE::DEFAULT:
            _window_system_logger->log_debug(U8StringBuilder{ "Создаем окно с дефолтными настройками рендера. Id окна: {0}"u8at }.fmt (0, window_id));
            break;
        case RENDER_PROVIDER_TYPE::OPENGL:
            _window_system_logger->log_debug(U8StringBuilder{ "Инициализируем окно рендером opengl. Id окна: {0}"u8at }.fmt(0, window_id));
            flags |= SDL_WINDOW_OPENGL;
            break;
        case RENDER_PROVIDER_TYPE::VULKAN:
            _window_system_logger->log_debug(U8StringBuilder{ "Инициализируем окно рендером vulkan. Id окна: {0}"u8at }.fmt(0, window_id));
            flags |= SDL_WINDOW_VULKAN;
            break;
        case RENDER_PROVIDER_TYPE::DX12:
            _window_system_logger->log_debug(U8StringBuilder{ "Инициализируем окно рендером DirectX12. Флаги не требуются. Id окна: {0}"u8at }.fmt(0, window_id));
            //flags |= SDL_WINDOW_VULKAN;
            break;
        case RENDER_PROVIDER_TYPE::METAL:
            _window_system_logger->log_debug(U8StringBuilder{ "Инициализируем окно рендером metal. Id окна: {0}"u8at }.fmt(0, window_id));
            flags |= SDL_WINDOW_METAL;
            break;
        default:
            _window_system_logger->log_error(U8StringBuilder{ "Окно не будет создано. Неопределенный тип рендера. Id окна: {0}"u8at}.fmt(0, window_id));
            throw new exceptions::window_system_exception(U8StringBuilder{ "Неопределенный тип рендера [{0}]"u8at }.fmt(0, (int)settings.draw_init_mode));
        }

        if (settings.borderless)
        {
            _window_system_logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_BORDERLESS));
            flags |= SDL_WINDOW_BORDERLESS;
        }

        if (settings.resizable)
        {
            _window_system_logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_RESIZABLE));
            flags |= SDL_WINDOW_RESIZABLE;
        }

        if (settings.grabbed)
        {
            _window_system_logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_INPUT_GRABBED));
            flags |= SDL_WINDOW_INPUT_GRABBED;
        }

        if (settings.highdpi)
        {
            _window_system_logger->log_debug("Добавляем флаг: "u8at + TO_STRING(SDL_WINDOW_ALLOW_HIGHDPI));
            flags |= SDL_WINDOW_ALLOW_HIGHDPI;
        }

        flags |= SDL_WINDOW_SHOWN;

        _window_system_logger->log_debug("Общее состояние флагов: "u8at + int_to_u8_at(flags));

        SDL_Window *window = SDL_CreateWindow(
            settings.lable.c_str(),
            settings.x_pos,
            settings.y_pos,
            settings.width,
            settings.height,
            flags);

        if (window == nullptr) {
            u8string_at err_description = SDL_GetError();
            _window_system_logger->log_error(U8StringBuilder{"sdl error: [{0}], window id: [{1}]"u8at}.fmt(0, err_description).fmt(1, window_id));
            throw exceptions::sdl_exception(err_description);
        }

        u8string_at logger_name = U8StringBuilder{ "render_system_logger_{0}"u8at }.fmt(0, window_id);
        _logger_manager->create_logger(logger_name, std::shared_ptr<ILogStrategy>(new FileLogStrategy(_config.log_file_name, 0)));
        auto _render_system_logger = _logger_manager->get_logger(logger_name);
        _render_system_logger->add_strategy(std::shared_ptr<ILogStrategy>(new ConsoleLogStrategy(0)));

        IRenderProvider* render_provider = get_render_provider(settings.draw_init_mode, _render_system_logger, window);

        _window_map[window_id] = std::shared_ptr<Window>(new Window(window_id, window, std::shared_ptr<IRenderProvider>(render_provider), settings.draw_init_mode));
        _window_map[window_id]->gui_tree = top_widget;

        //_render_provider = at::core::gui::render::get_render_provider(settings.draw_init_mode, std::shared_ptr(_logger), window);
        //_render_provider->prepare_new_frame(settings.backgroud_color);

        SDL_ShowWindow(window);

        //SDL_Delay(3000);

        return _window_map[window_id];
    }
}