cmake_minimum_required(VERSION 3.8)

project(atge)

set(ENTER_POINT "./main.cpp")

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

set(WindowSystem 
"./Core/WindowSystem/ATPreloadWindowInitializeSettings.hpp"
"./Core/WindowSystem/ATWindowInitializeSettings.hpp"
"./Core/WindowSystem/ATWindowContext.hpp"
"./Core/WindowSystem/ATWindowManager.cpp"
"./Core/WindowSystem/ATWindowManager.hpp")

set(CORE "./Core/ATCore.hpp" ${WindowSystem})

add_executable(atge ${ENTER_POINT} ${UTILS} ${CORE})

macro(add_and_link_sdl2)
    set (SDL2_DIR "../third_party_libs/SDL2-2.0.14")
    find_package(SDL2 REQUIRED)

    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/third_party_libs/SDL2-2.0.14/include")

    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/third_party_libs/SDL2-2.0.14/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/third_party_libs/SDL2-2.0.14/lib/x64/SDL2main.lib")
    else ()
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/third_party_libs/SDL2-2.0.14/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/third_party_libs/SDL2-2.0.14/lib/x86/SDL2main.lib")
    endif ()

    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(atge ${SDL2_LIBRARIES})

    MESSAGE("SDL2 include path:" ${SDL2_INCLUDE_DIRS})
    MESSAGE("SDL2 library path:" ${SDL2_LIBRARIES})
endmacro()

add_and_link_sdl2()

set_target_properties(atge PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# cmake ../
# cmake --build .