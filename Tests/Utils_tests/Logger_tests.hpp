#include "SharedUtilsInclude.hpp"

#include <fstream>
#include <regex>

BOOST_AUTO_TEST_SUITE(log_system_tests)

BOOST_AUTO_TEST_CASE(test_create_logger_and_delete_before_log_manager_release)
{
    const u8string_at log_file_path = "./test_create_logger_and_delete_before_log_manager_release.log";
    at::utils::log_system::logger::at_interface::AbstractLogger *logger = nullptr;
    at::utils::log_system::LoggerManager log_manager{};
    log_manager.create_logger("test_create_logger_and_delete_before_log_manager_release", new at::utils::log_system::strategy::DefaultFileLogStrategy(log_file_path));
    BOOST_REQUIRE(logger == nullptr);
    logger = log_manager.get_logger("test_create_logger_and_delete_before_log_manager_release");

    //BOOST_TEST(logger);
    BOOST_REQUIRE(logger != nullptr);

    delete logger;
    logger = nullptr;

    remove(log_file_path.c_str());
}

//you can log after log manager deleted
BOOST_AUTO_TEST_CASE(test_create_logger_and_delete_after_log_manager_release)
{
    const u8string_at log_file_path = "./test_create_logger_and_delete_after_log_manager_release.log";
    at::utils::log_system::logger::at_interface::AbstractLogger *logger = nullptr;
    {
        at::utils::log_system::LoggerManager log_manager{};
        log_manager.create_logger("test_create_logger_and_delete_after_log_manager_release", new at::utils::log_system::strategy::DefaultFileLogStrategy(log_file_path));
        logger = log_manager.get_logger("test_create_logger_and_delete_after_log_manager_release");

        //BOOST_TEST(logger);
        BOOST_REQUIRE(logger != nullptr);
    }
    delete logger;
    logger = nullptr;

    remove(log_file_path.c_str());
}

BOOST_AUTO_TEST_CASE(test_log_info)
{
    const u8string_at log_file_path = "./test_log_info.log";
    const u8string_at write_log = "вцв dawdaw3231 дда 佐藤 幹夫";

    at::utils::log_system::logger::at_interface::AbstractLogger *logger = nullptr;
    {
        at::utils::log_system::LoggerManager log_manager{};
        log_manager.create_logger("test_log_info", new at::utils::log_system::strategy::DefaultFileLogStrategy(log_file_path));
        logger = log_manager.get_logger("test_log_info");

        //BOOST_TEST(logger);
        BOOST_REQUIRE(logger != nullptr);
    }

    logger->log_info(write_log);

    delete logger;
    logger = nullptr;

    std::ifstream file_stream(log_file_path);

    file_stream.seekg(0, std::ios::end);
    std::streampos length = file_stream.tellg();
    char *buffer = new char[length];

    file_stream.seekg(0, std::ios::beg);
    file_stream.read(buffer, length);

    file_stream.close();

    u8string_at log_data(buffer);
    delete buffer;

    BOOST_REQUIRE(log_data.find_first_of(write_log) != u32string_at::npos //
                  && (log_data.find_first_of("INFO") != u32string_at::npos || log_data.find_first_of("info") != u32string_at::npos));

    remove(log_file_path.c_str());
}

BOOST_AUTO_TEST_CASE(test_log_error)
{
    const u8string_at log_file_path = "./test_log_error.log";
    const u8string_at write_log = "вцв dawdaw3231 дда 佐藤 幹夫";

    at::utils::log_system::logger::at_interface::AbstractLogger *logger = nullptr;
    {
        at::utils::log_system::LoggerManager log_manager{};
        log_manager.create_logger("test_log_error", new at::utils::log_system::strategy::DefaultFileLogStrategy(log_file_path));
        logger = log_manager.get_logger("test_log_error");

        //BOOST_TEST(logger);
        BOOST_REQUIRE(logger != nullptr);
    }

    logger->log_error(write_log);

    delete logger;
    logger = nullptr;

    std::ifstream file_stream(log_file_path);

    file_stream.seekg(0, std::ios::end);
    std::streampos length = file_stream.tellg();
    char *buffer = new char[length];

    file_stream.seekg(0, std::ios::beg);
    file_stream.read(buffer, length);

    file_stream.close();

    u8string_at log_data(buffer);
    delete buffer;

    BOOST_REQUIRE(log_data.find_first_of(write_log) != u32string_at::npos //
                  && (log_data.find_first_of("ERROR") != u32string_at::npos || log_data.find_first_of("error") != u32string_at::npos));

    remove(log_file_path.c_str());
}

BOOST_AUTO_TEST_CASE(test_log_debug)
{
    const u8string_at log_file_path = "./test_log_debug.log";
    const u8string_at write_log = "вцв dawdaw3231 дда 佐藤 幹夫";

    at::utils::log_system::logger::at_interface::AbstractLogger *logger = nullptr;
    {
        at::utils::log_system::LoggerManager log_manager{};
        log_manager.create_logger("test_log_debug", new at::utils::log_system::strategy::DefaultFileLogStrategy(log_file_path));
        logger = log_manager.get_logger("test_log_debug");

        //BOOST_TEST(logger);
        BOOST_REQUIRE(logger != nullptr);
    }

    logger->log_error(write_log);

    delete logger;
    logger = nullptr;

    std::ifstream file_stream(log_file_path);

    file_stream.seekg(0, std::ios::end);
    std::streampos length = file_stream.tellg();
    char *buffer = new char[length];

    file_stream.seekg(0, std::ios::beg);
    file_stream.read(buffer, length);

    file_stream.close();

    u8string_at log_data(buffer);
    delete buffer;

    BOOST_REQUIRE(log_data.find_first_of(write_log) != u32string_at::npos //
                  && (log_data.find_first_of("DEBUG") != u32string_at::npos || log_data.find_first_of("debug") != u32string_at::npos));

    remove(log_file_path.c_str());
}

BOOST_AUTO_TEST_CASE(test_log_warning)
{
    const u8string_at log_file_path = "./test_log_warning.log";
    const u8string_at write_log = "вцв dawdaw3231 дда 佐藤 幹夫";

    at::utils::log_system::logger::at_interface::AbstractLogger *logger = nullptr;
    {
        at::utils::log_system::LoggerManager log_manager{};
        log_manager.create_logger("test_log_warning", new at::utils::log_system::strategy::DefaultFileLogStrategy(log_file_path));
        logger = log_manager.get_logger("test_log_warning");

        //BOOST_TEST(logger);
        BOOST_REQUIRE(logger != nullptr);
    }

    logger->log_error(write_log);

    delete logger;
    logger = nullptr;

    std::ifstream file_stream(log_file_path);

    file_stream.seekg(0, std::ios::end);
    std::streampos length = file_stream.tellg();
    char *buffer = new char[length];

    file_stream.seekg(0, std::ios::beg);
    file_stream.read(buffer, length);

    file_stream.close();

    u8string_at log_data(buffer);
    delete buffer;

    BOOST_REQUIRE(log_data.find_first_of(write_log) != u32string_at::npos //
                  && (log_data.find_first_of("WARNING") != u32string_at::npos || log_data.find_first_of("warning") != u32string_at::npos));

    remove(log_file_path.c_str());
}

BOOST_AUTO_TEST_CASE(test_log_fatal)
{
    setlocale(LC_ALL, "");
    const u8string_at log_file_path = "./test_log_fatal.log";
    const u8string_at write_log = "вцв dawdaw3231 дда 佐藤 幹夫";

    at::utils::log_system::logger::at_interface::AbstractLogger *logger = nullptr;
    {
        at::utils::log_system::LoggerManager log_manager{};
        log_manager.create_logger("test_log_fatal", new at::utils::log_system::strategy::DefaultFileLogStrategy(log_file_path));
        logger = log_manager.get_logger("test_log_fatal");

        //BOOST_TEST(logger);
        BOOST_REQUIRE(logger != nullptr);
    }

    logger->log_error(write_log);

    delete logger;
    logger = nullptr;

    std::ifstream file_stream(log_file_path);

    file_stream.seekg(0, std::ios::end);
    std::streampos length = file_stream.tellg();
    char *buffer = new char[length];

    file_stream.seekg(0, std::ios::beg);
    file_stream.read(buffer, length);

    file_stream.close();

    u8string_at log_data(buffer);
    delete buffer;

    BOOST_REQUIRE(log_data.find_first_of(write_log) != u32string_at::npos //
                  && (log_data.find_first_of("FATAL") != u32string_at::npos || log_data.find_first_of("fatal") != u32string_at::npos));

    remove(log_file_path.c_str());
}

BOOST_AUTO_TEST_SUITE_END()