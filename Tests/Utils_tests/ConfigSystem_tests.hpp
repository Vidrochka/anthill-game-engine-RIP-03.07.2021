#include "SharedUtilsInclude.hpp"

#include <fstream>

BOOST_AUTO_TEST_SUITE(config_system_tests)

BOOST_AUTO_TEST_CASE(test_config_toml_read_one_param_one_section_in_config)
{
    const u8string_at file_name = "./test_config_toml_read_one_param_one_section_in_config.toml";
    std::ofstream file(file_name, std::ios::app);

    BOOST_REQUIRE_EQUAL(file.is_open(), true);

    file << "[test1]\ntest_key = \"test_value1\"";

    file.flush();
    file.close();

    at::utils::config_system::source::at_interface::IConfigSourceInterface *source //
        = new at::utils::config_system::source::DefaultFileConfigSource(file_name);

    BOOST_REQUIRE(source);

    at::utils::config_system::parsing_strategy::at_interface::IDynamicParsingStrategy *strategy //
        = new at::utils::config_system::parsing_strategy::TomlDynamicParsingStrategy();

    BOOST_REQUIRE(strategy);

    auto config = at::utils::config_system::ConfigManager::get_config(source, strategy);

    BOOST_REQUIRE(config);

    delete source;
    delete strategy;

    //you cant remove file before delete source, because source has file stream
    remove(file_name.c_str());

    auto res = config->get_section("test1")->get_value("test_key");
    BOOST_REQUIRE_EQUAL(res, "test_value1");

    delete config;
}

BOOST_AUTO_TEST_CASE(test_config_toml_read_one_param_two_section_in_config)
{
    const u8string_at file_name = "./test_config_toml_read_one_param_two_section_in_config.toml";
    std::ofstream file(file_name, std::ios::app);

    BOOST_REQUIRE_EQUAL(file.is_open(), true);

    file << "[test1]\ntest_key = \"test_value1\"\n\n[test2]\ntest_key = \"test_value2\"";

    file.flush();
    file.close();

    at::utils::config_system::source::at_interface::IConfigSourceInterface *source //
        = new at::utils::config_system::source::DefaultFileConfigSource(file_name);

    BOOST_REQUIRE(source);

    at::utils::config_system::parsing_strategy::at_interface::IDynamicParsingStrategy *strategy //
        = new at::utils::config_system::parsing_strategy::TomlDynamicParsingStrategy();

    BOOST_REQUIRE(strategy);

    auto config = at::utils::config_system::ConfigManager::get_config(source, strategy);

    BOOST_REQUIRE(config);

    delete source;
    delete strategy;

    //you cant remove file before delete source, because source has file stream
    remove(file_name.c_str());

    auto res = config->get_section("test2")->get_value("test_key");
    BOOST_REQUIRE_EQUAL(res, "test_value2");

    res = config->get_section("test1")->get_value("test_key");
    BOOST_REQUIRE_EQUAL(res, "test_value1");

    delete config;
}

BOOST_AUTO_TEST_CASE(test_config_toml_read_one_param_two_section_in_config_with_nested_section)
{
    const u8string_at file_name = "./test_config_toml_read_one_param_two_section_in_config_with_nested_section.toml";
    std::ofstream file(file_name, std::ios::app);

    BOOST_REQUIRE_EQUAL(file.is_open(), true);

    file << "[test1]\ntest_key = \"test_value1\"\n\n[test2]\ntest_key = \"test_value2\"\n\t[test3]\n\ttest_key = \"test_value3\"";

    file.flush();
    file.close();

    at::utils::config_system::source::at_interface::IConfigSourceInterface *source //
        = new at::utils::config_system::source::DefaultFileConfigSource(file_name);

    BOOST_REQUIRE(source);

    at::utils::config_system::parsing_strategy::at_interface::IDynamicParsingStrategy *strategy //
        = new at::utils::config_system::parsing_strategy::TomlDynamicParsingStrategy();

    BOOST_REQUIRE(strategy);

    auto config = at::utils::config_system::ConfigManager::get_config(source, strategy);

    BOOST_REQUIRE(config);

    delete source;
    delete strategy;

    //you cant remove file before delete source, because source has file stream
    remove(file_name.c_str());

    auto res = config->get_section("test2")->get_section("test3")->get_value("test_key");
    BOOST_REQUIRE_EQUAL(res, "test_value3");

    delete config;
}

BOOST_AUTO_TEST_SUITE_END()