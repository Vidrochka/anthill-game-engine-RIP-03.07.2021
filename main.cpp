#include <string>
#include <iostream>
#include "Utils/Utils.hpp"
#include <locale.h>

int main()
{
    try
    {
        setlocale(LC_ALL, "");
        at::utils::logger_manager::LoggerManager::create_logger(L"test", new at::utils::logger_manager::strategy::DefaultFileLogStrategy{L"./text1.log", 6});
        auto logger = at::utils::logger_manager::LoggerManager::get_logger(L"test");
        //LOG_ARGS4(L"1", L"2", L"3", L"4")
        logger->add_strategy(new at::utils::logger_manager::strategy::DefaultFileLogStrategy{L"./test2.log", 5});
        logger->log_debug(L"test 1");
        //logger->log_debug(L"b test 1 дда 佐藤 幹夫 ");
        logger->log_error(L"test 2");

        at::utils::config_manager::source::interface::IConfigSourceInterface *source = new at::utils::config_manager::source::DefaultFileConfigSource(L"./test.toml");
        at::utils::config_manager::parsing_strategy::interface::IParsingStrategy *strategy = new at::utils::config_manager::parsing_strategy::TomlParsingStrategy();
        auto config = at::utils::config_manager::ConfigManager::get_config(source, strategy);

        logger->log_info(config->get_section(L"default")->get_value(L"test"));

        delete source;
        delete strategy;
        //logger.flush();
        logger->log_fatal(L"test 3", 2, LINE_STAMP);
        logger->log_error(L"test 4");
    }
    catch (std::string err_msg)
    {
        return 1;
    }

    return 0;
}