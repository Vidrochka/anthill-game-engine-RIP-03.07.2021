//#include <string>
#include <iostream>
#include "Core/ATCore.hpp"
#include "Utils/Utils.hpp"
#include <locale.h>

int main(int argc, char *argv[])
{
    std::shared_ptr<at::utils::log_system::logger::at_interface::ILogger> logger;
    try
    {
        setlocale(LC_ALL, "");
        at::utils::log_system::LoggerManager log_manager{};
        log_manager.create_logger("test"u8at);
        logger = log_manager.get_logger("test"u8at);
        logger->add_strategy(new at::utils::log_system::strategy::DefaultFileLogStrategy{"./test2.log"u8at, 5});
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what();
        return 1;
    }

    try
    {
        std::ifstream main_config("main_config.json"u8at);
        json json_box;
        main_config >> json_box;

        auto preload_window_settings = json_box["preload_window_settings"u8at].get<at::core::window_system::preload_window_initialize_settings::PreloadWindowInitializeSettings>();

        logger->log_debug(int_to_u8_at(preload_window_settings.width));
        logger->log_debug(int_to_u8_at(preload_window_settings.height));
        logger->log_debug(preload_window_settings.lable);
        //logger->log_debug(int_to_u8_at((int)preload_window_settings.open_mode));

        at::core::window_system::window_manager::WindowManager window_manager{std::shared_ptr<ILogger>(logger)};
        window_manager.open_preload_window(preload_window_settings);// .open_new_window(main_window_settings);
        logger->flush();
        std::cin.get();
    }
    catch (const std::exception& ex)
    {
        logger->log_error(ex.what());
        std::cout << ex.what();
        logger->flush();
        return 1;
    }

    return 0;
}