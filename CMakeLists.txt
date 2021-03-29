cmake_minimum_required(VERSION 3.8)

project(atge)

set(EXE "./main.cpp")

set(LOGGING 
"./Utils/Logger/ATLogger.hpp" 
"./Utils/Logger/ATLogger.cpp" 
"./Utils/Logger/ATLoggerDefineExtensions.hpp" 
"./Utils/Logger/ATLoggerEvent.hpp"
"./Utils/Logger/ATLoggerStrategy.hpp"
"./Utils/Logger/ATLoggerStrategy.cpp"
"./Utils/Logger/ATLoggerManager.hpp"
"./Utils/Logger/ATLoggerManager.cpp"
)

set(ConfigManager
"./Utils/ConfigManager/ATConfig.hpp"
"./Utils/ConfigManager/ATConfig.cpp"
"./Utils/ConfigManager/ATConfigManager.hpp"
"./Utils/ConfigManager/ATConfigManager.cpp"
"./Utils/ConfigManager/ATConfigParsingStrategy.hpp"
"./Utils/ConfigManager/ATConfigParsingStrategy.cpp"
"./Utils/ConfigManager/ATConfigSource.hpp"
"./Utils/ConfigManager/ATConfigSource.cpp"
)

set(Types
"./Utils/Types/ATString.hpp"
)

set(UTILS "./Utils/Utils.hpp" ${LOGGING} ${ConfigManager} ${Types})

add_executable(main ${EXE} ${UTILS})

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# cmake ../
# cmake --build .