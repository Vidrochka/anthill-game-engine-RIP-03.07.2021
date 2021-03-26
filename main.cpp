#include <string>
#include <iostream>
#include "Utils/Utils.hpp"

void print_check(std::string msg)
{
    std::cout << msg << std::endl;
}

int main()
{
    try
    {
        at::utils::logger::ATLogger::init_base_logger();
        at::utils::logger::ATLogger::create_section("test", "./test.log", 0);
        at::utils::logger::interface::ILogger *logger = new at::utils::logger::ATLogger("test");
        LOG_ARGS4("1", "2", "3", "4")
        logger->add_callback(print_check);
        logger->add_callback(print_check);
        logger->log_debug("test 1");
        ((at::utils::logger::ATLogger *)logger)->b_log_debug("b test 1 дда 佐藤 幹夫");
        logger->log_error("test 2");
        //logger.flush();
        logger->log_fatal("test 3", 2);
        logger->log_error("test 4");
    }
    catch (std::string err_msg)
    {
        return 1;
    }

    return 0;
}