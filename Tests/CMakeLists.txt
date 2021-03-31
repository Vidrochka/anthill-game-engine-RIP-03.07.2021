cmake_minimum_required(VERSION 3.8)

project(atge_test)

set (TESTS_SOURCES
	"./test.cpp"
    "./SharedIncludes.hpp"
    "./Utils_tests/Logger_tests.hpp")

set(LOGGING 
"../Utils/Logger/ATLogger.hpp" 
"../Utils/Logger/ATLogger.cpp" 
"../Utils/Logger/ATLoggerDefineExtensions.hpp" 
"../Utils/Logger/ATLoggerEvent.hpp"
"../Utils/Logger/ATLoggerStrategy.hpp"
"../Utils/Logger/ATLoggerStrategy.cpp"
"../Utils/Logger/ATLoggerManager.hpp"
"../Utils/Logger/ATLoggerManager.cpp"
)

set(ConfigManager
"../Utils/ConfigManager/ATConfig.hpp"
"../Utils/ConfigManager/ATConfig.cpp"
"../Utils/ConfigManager/ATConfigManager.hpp"
"../Utils/ConfigManager/ATConfigManager.cpp"
"../Utils/ConfigManager/ATConfigParsingStrategy.hpp"
"../Utils/ConfigManager/ATConfigParsingStrategy.cpp"
"../Utils/ConfigManager/ATConfigSource.hpp"
"../Utils/ConfigManager/ATConfigSource.cpp"
)

set(Types
"../Utils/Types/ATString.hpp"
)

set_source_files_properties(
"../Utils/Types/ATString.hpp"
PROPERTIES
COMPILE_FLAGS "/wd4996")

set(UTILS "../Utils/Utils.hpp" ${LOGGING} ${ConfigManager} ${Types})

set (BOOST_ROOT "../third_party_libs/boost_1_75_0")
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set (TEST test_atge)

add_executable (${TEST} ${TESTS_SOURCES} ${UTILS})

target_link_libraries (${TEST} ${PROJECT} ${Boost_LIBRARIES})

enable_testing()

add_test (${TEST} ${TEST})

#add_executable(test_cases )

#target_link_libraries(test_cases ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

#add_test(NAME test1 COMMAND test_cases)

set_target_properties(${TEST} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)