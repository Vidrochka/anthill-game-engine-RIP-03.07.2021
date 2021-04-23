cmake_minimum_required (VERSION 3.8)

project (anthill-game-engine-utils)

set(types
 "guid/ATGuid.hpp" 
 "guid/ATGuidExceptions.hpp"
 )


set(log_system
"log-system/ATLogger.cpp"
"log-system/ATLoggerManager.cpp"
"log-system/log-strategy/ATConsoleLogStrategy.cpp"
"log-system/log-strategy/ATFileLogStrategy.cpp"
"log-system/log-strategy/ATLoggerStrategyUtils.cpp"
 "log-system/ATLogMsg.hpp")

set(types
"types/ATColor.cpp"
"types/ATString.cpp"
)

include_directories("types/" "log-system/log-strategy/" "log-system/")

set (BOOST_ROOT "../third-party-libs/boost_1_75_0")
find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories("../third-party-libs/boost_1_75_0/")

add_library(anthill-game-engine-utils STATIC ${log_system} ${types})

set_target_properties (anthill-game-engine-utils PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)