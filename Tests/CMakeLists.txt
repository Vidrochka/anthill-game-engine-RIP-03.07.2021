cmake_minimum_required(VERSION 3.8)

project(atge_test)

set (TESTS_SOURCES
	"./test.cpp"
    "./SharedIncludes.hpp"
    "./Utils_tests/Logger_tests.hpp"
    "./Utils_tests/ConfigSystem_tests.hpp")

set(LOGGING 
"../Utils/LogSystem/ATLogger.hpp" 
"../Utils/LogSystem/ATLogger.cpp" 
"../Utils/LogSystem/ATLoggerDefineExtensions.hpp" 
"../Utils/LogSystem/ATLoggerEvent.hpp"
"../Utils/LogSystem/ATLoggerStrategy.hpp"
"../Utils/LogSystem/ATLoggerStrategy.cpp"
"../Utils/LogSystem/ATLoggerManager.hpp"
"../Utils/LogSystem/ATLoggerManager.cpp"
)

set(ConfigSystem
"../Utils/ConfigSystem/ATConfig.hpp"
"../Utils/ConfigSystem/ATConfig.cpp"
"../Utils/ConfigSystem/ATConfigManager.hpp"
"../Utils/ConfigSystem/ATConfigManager.cpp"
"../Utils/ConfigSystem/ATConfigParsingStrategy.hpp"
"../Utils/ConfigSystem/ATConfigParsingStrategy.cpp"
"../Utils/ConfigSystem/ATConfigSource.hpp"
"../Utils/ConfigSystem/ATConfigSource.cpp"
)

set(Types
"../Utils/Types/ATString.hpp"
)

set_source_files_properties(
"../Utils/Types/ATString.hpp"
PROPERTIES
COMPILE_FLAGS "/wd4996")

set(UTILS "../Utils/Utils.hpp" ${LOGGING} ${ConfigSystem} ${Types})

set (BOOST_ROOT "../third_party_libs/boost_1_75_0")
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set (TEST test_atge)

add_executable (${TEST} ${TESTS_SOURCES} ${UTILS})

target_link_libraries (${TEST} ${PROJECT} ${Boost_LIBRARIES})

enable_testing()

add_test (${TEST} ${TEST})

set_target_properties(${TEST} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)