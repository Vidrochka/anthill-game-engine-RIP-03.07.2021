cmake_minimum_required(VERSION 3.8)

project(atge)

set(EXE "./main.cpp")

set(LOGGING 
"./Utils/LogSystem/ATLogger.hpp" 
"./Utils/LogSystem/ATLogger.cpp" 
"./Utils/LogSystem/ATLoggerDefineExtensions.hpp" 
"./Utils/LogSystem/ATLoggerEvent.hpp"
"./Utils/LogSystem/ATLoggerStrategy.hpp"
"./Utils/LogSystem/ATLoggerStrategy.cpp"
"./Utils/LogSystem/ATLoggerManager.hpp"
"./Utils/LogSystem/ATLoggerManager.cpp"
)

set(ConfigSystem
"./Utils/ConfigSystem/ATConfig.hpp"
"./Utils/ConfigSystem/ATConfig.cpp"
"./Utils/ConfigSystem/ATConfigManager.hpp"
"./Utils/ConfigSystem/ATConfigManager.cpp"
"./Utils/ConfigSystem/ATConfigParsingStrategy.hpp"
"./Utils/ConfigSystem/ATConfigParsingStrategy.cpp"
"./Utils/ConfigSystem/ATConfigSource.hpp"
"./Utils/ConfigSystem/ATConfigSource.cpp"
)

set(Types
"./Utils/Types/ATString.hpp"
)

set_source_files_properties(
"./Utils/Types/ATString.hpp"
PROPERTIES
COMPILE_FLAGS "/wd4996")

set(UTILS "./Utils/Utils.hpp" ${LOGGING} ${ConfigSystem} ${Types})

add_executable(main ${EXE} ${UTILS})

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# cmake ../
# cmake --build .