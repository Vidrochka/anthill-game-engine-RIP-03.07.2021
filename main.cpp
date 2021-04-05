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

        std::ifstream main_config("main_config.json");
        json json_box;
        main_config >> json_box;

        auto main_window_settings = json_box["main_window_settings"].get<at::core::window_system::window_initialize_settings::WindowInitializeSettings>();

        logger->log_debug(int_to_u8_at(main_window_settings.width));
        logger->log_debug(int_to_u8_at(main_window_settings.height));
        logger->log_debug(main_window_settings.lable);
        logger->log_debug(int_to_u8_at((int)main_window_settings.open_mode));

        at::core::window_system::window_manager::WindowManager window_manager{std::shared_ptr<ILogger>(logger)};
        window_manager.open_new_window(main_window_settings);
        logger->flush();
        std::cin.get();
    }
    catch (std::exception ex)
    {
        std::cout << ex.what();
        return 1;
    }

    return 0;
}