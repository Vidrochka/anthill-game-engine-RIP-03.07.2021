#include <string>
#include <iostream>
#include "Utils/Utils.hpp"

int main()
{
    try
    {
        at::utils::logger::ATLogger::init_base_logger();
        at::utils::logger::ATLogger::create_section("test", new at::utils::logger::strategy::DefaultFileLogStrategy{"./text1.log", 6});
        at::utils::logger::interface::ILogger *logger = new at::utils::logger::ATLogger("test");
        LOG_ARGS4("1", "2", "3", "4")
        logger->add_strategy(new at::utils::logger::strategy::DefaultFileLogStrategy{"./test2.log", 5});
        logger->log_debug("test 1");
        ((at::utils::logger::ATLogger *)logger)->b_log_debug("b test 1 дда 佐藤 幹夫");
        logger->log_error("test 2");
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