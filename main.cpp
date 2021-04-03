//#include <string>
#include <iostream>
#include "Core/ATCore.hpp"
#include "Utils/Utils.hpp"
#include <locale.h>

int main(int argc, char *argv[])
{
    try
    {
        setlocale(LC_ALL, "");
        at::utils::log_system::LoggerManager log_manager{};
        log_manager.create_logger("test");
        auto logger = log_manager.get_logger("test");
        logger->add_strategy(new at::utils::log_system::strategy::DefaultFileLogStrategy{"./test2.log", 5});
        at::core::window_system::window_manager::WindowManager window_manager{std::shared_ptr<ILogger>(logger)};
        window_manager.open_new_window(
            *(at::core::window_system::window_initialize_settings::WindowInitializeSettings("Test")
                  .set_resizable(false)
                  ->set_backgroud_color(at::type::color::RGBA_at<uint8_t>::get_black())));
        logger->flush();
        std::cin.get();

        /*//LOG_ARGS4(L"1", L"2", L"3", L"4")
        logger->add_strategy(new at::utils::log_system::strategy::DefaultFileLogStrategy{"./test2.log", 5});
        logger->log_debug("test 1");
        logger->log_debug("b test 1 дда 佐藤 幹夫 ");
        logger->log_error("test 2");
        std::cout << "1" << std::endl;
        at::utils::config_system::source::at_interface::IConfigSourceInterface *source = new at::utils::config_system::source::DefaultFileConfigSource("./test.toml");
        std::cout << "2" << std::endl;
        at::utils::config_system::parsing_strategy::at_interface::IParsingStrategy *strategy = new at::utils::config_system::parsing_strategy::TomlParsingStrategy();
        std::cout << "3" << std::endl;
        auto config = at::utils::config_system::ConfigManager::get_config(source, strategy);
        std::cout << "4" << std::endl;
        logger->log_info(config->get_section("default")->get_value("test"));

        delete source;
        delete strategy;
        //logger.flush();
        logger->log_fatal("test 3", 2, LINE_STAMP);
        logger->log_error("test 4");*/
    }
    catch (std::exception ex)
    {
        std::cout << ex.what();
        return 1;
    }

    return 0;
}

/*int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "SDL2Test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 68, 68, 68, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}*/