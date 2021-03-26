#include <string>
#include <iostream>
#include "../Utils/Include/ATLogger.hpp"
#include "../Utils/Include/ATDefineExtensions.hpp"

int main()
{
    try
    {
        at::utils::logger::ATLogger::init_base_logger();
        at::utils::logger::ATLogger::create_section("test", "./test.log");
        at::utils::logger::ATLogger logger("test");
        LOG_ARGS4("1", "2", "3", "4")
        logger.log_debug("test 1");
        logger.b_log_debug("b test 1 дда 佐藤 幹夫");
        logger.log_error("test 2");
        //logger.flush();
        logger.log_fatal("test 3", 2);
        logger.log_error("test 4");
    }
    catch (std::string err_msg)
    {
        return 1;
    }

    return 0;
}