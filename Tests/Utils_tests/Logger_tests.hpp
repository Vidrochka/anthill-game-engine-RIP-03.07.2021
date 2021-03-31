#include "SharedUtilsInclude.hpp"

BOOST_AUTO_TEST_SUITE(logger_tests)

BOOST_AUTO_TEST_CASE(test_create_logger_and_delete_before_log_manager_release)
{
    at::utils::logger_manager::logger::at_interface::AbstractLogger *logger = nullptr;
    at::utils::logger_manager::LoggerManager log_manager{};
    log_manager.create_logger("test_create_logger_and_delete_before_log_manager_release");
    BOOST_REQUIRE(logger == nullptr);
    logger = log_manager.get_logger("test_create_logger_and_delete_before_log_manager_release");

    //BOOST_TEST(logger);
    BOOST_REQUIRE(logger != nullptr);

    delete logger;
    logger = nullptr;
}

BOOST_AUTO_TEST_CASE(test_create_logger_and_delete_after_log_manager_release)
{
    at::utils::logger_manager::logger::at_interface::AbstractLogger *logger = nullptr;
    {
        at::utils::logger_manager::LoggerManager log_manager{};
        log_manager.create_logger("test_create_logger_and_delete_after_log_manager_release");
        logger = log_manager.get_logger("test_create_logger_and_delete_after_log_manager_release");

        //BOOST_TEST(logger);
        BOOST_REQUIRE(logger != nullptr);
    }
    delete logger;
    logger = nullptr;
}

BOOST_AUTO_TEST_SUITE_END()