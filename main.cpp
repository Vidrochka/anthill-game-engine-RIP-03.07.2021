//#include <string>
#include <iostream>
#include "Utils/Utils.hpp"
#include <locale.h>

int main()
{
    try
    {
        setlocale(LC_ALL, "");
        at::utils::logger_manager::LoggerManager log_manager{};
        log_manager.create_logger("test");
        at::utils::logger_manager::logger::at_interface::AbstractLogger *logger = log_manager.get_logger("test");
        //LOG_ARGS4(L"1", L"2", L"3", L"4")
        logger->add_strategy(new at::utils::logger_manager::strategy::DefaultFileLogStrategy{"./test2.log", 5});
        logger->log_debug("test 1");
        logger->log_debug("b test 1 дда 佐藤 幹夫 ");
        logger->log_error("test 2");
        std::cout << "1" << std::endl;
        at::utils::config_manager::source::at_interface::IConfigSourceInterface *source = new at::utils::config_manager::source::DefaultFileConfigSource(U"./test.toml");
        std::cout << "2" << std::endl;
        at::utils::config_manager::parsing_strategy::at_interface::IParsingStrategy *strategy = new at::utils::config_manager::parsing_strategy::TomlParsingStrategy();
        std::cout << "3" << std::endl;
        auto config = at::utils::config_manager::ConfigManager::get_config(source, strategy);
        std::cout << "4" << std::endl;
        logger->log_info(config->get_section("default")->get_value("test"));

        delete source;
        delete strategy;
        //logger.flush();
        logger->log_fatal("test 3", 2, LINE_STAMP);
        logger->log_error("test 4");
    }
    catch (std::string err_msg)
    {
        return 1;
    }

    return 0;
}