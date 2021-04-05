##########################################
#              Main Settings             #
##########################################
cmake_minimum_required (VERSION 3.8)

project (atge)

set (
    ENTER_POINT 
    "../main.cpp"
)

set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

###########################################

##########################################
#              Logger files              #
##########################################
set (
    LOGGING 
    "../Utils/LogSystem/ATLogger.hpp" 
    "../Utils/LogSystem/ATLogger.cpp" 
    "../Utils/LogSystem/ATLoggerContext.hpp"
    "../Utils/LogSystem/ATLoggerDefineExtensions.hpp" 
    "../Utils/LogSystem/ATLoggerEvent.hpp"
    "../Utils/LogSystem/ATLoggerExceptions.hpp"
    "../Utils/LogSystem/ATLoggerManager.cpp"
    "../Utils/LogSystem/ATLoggerManager.hpp"
    "../Utils/LogSystem/ATLoggerStrategy.cpp"
    "../Utils/LogSystem/ATLoggerStrategy.hpp"
)
###########################################


##########################################
#              File converters           #
##########################################
set (
    JSON 
    "../third_party_libs/json/single_include/nlohmann/json.hpp"
)
##########################################

##########################################
#          Castom anthill types          #
##########################################
set (
    Types
    "../Utils/Types/ATString.hpp"
    "../Utils/Types/ATString.cpp"
    "../Utils/Types/ATColor.cpp"
    "../Utils/Types/ATColor.hpp"
)
##########################################

##########################################
#                NOT NEED                #
##########################################
#set_source_files_properties(
#"../Utils/Types/ATString.hpp"
#PROPERTIES
#COMPILE_FLAGS "/wd4996")
##########################################

##########################################
#               Utils header             #
##########################################
set (UTILS "../Utils/Utils.hpp" ${LOGGING} ${Types} ${JSON})
##########################################

##########################################
#              Window system             #
##########################################
set (WindowSystem 
"../Core/WindowSystem/ATPreloadWindowInitializeSettings.hpp"
"../Core/WindowSystem/ATWindowInitializeSettings.hpp"
"../Core/WindowSystem/ATWindowInitializeSettings.cpp"
"../Core/WindowSystem/ATWindowContext.hpp"
"../Core/WindowSystem/ATWindowManager.cpp"
"../Core/WindowSystem/ATWindowManager.hpp")
##########################################

##########################################
#               Core header              #
##########################################
set (CORE "../Core/ATCore.hpp" ${WindowSystem})
##########################################

##########################################
#             Make executable            #
##########################################
add_executable (atge ${ENTER_POINT} ${UTILS} ${CORE})
##########################################

##########################################
#            Define SDL2 macros          #
##########################################
macro (add_and_link_sdl2)
    set (SDL2_DIR "../third_party_libs/SDL2-2.0.14")
    find_package (SDL2 REQUIRED)

    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../third_party_libs/SDL2-2.0.14/include")

    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set (SDL2_ALL_LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/../third_party_libs/SDL2-2.0.14/lib/x64/")
        set (SDL2_LIBRARY_NAME "SDL2.lib;")
        set (SDL2_MAIN_LIBRARY_NAME "SDL2main.lib")
    else ()
        set (SDL2_ALL_LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/../third_party_libs/SDL2-2.0.14/lib/x86/")
        set (SDL2_LIBRARY_NAME "SDL2.lib;")
        set (SDL2_MAIN_LIBRARY_NAME "SDL2main.lib")
    endif ()

    include_directories (${SDL2_INCLUDE_DIRS})
    target_link_libraries (atge ${SDL2_ALL_LIBS_PATH}${SDL2_LIBRARY_NAME})
    target_link_libraries (atge ${SDL2_ALL_LIBS_PATH}${SDL2_MAIN_LIBRARY_NAME})

    MESSAGE ("SDL2 include path:" ${SDL2_INCLUDE_DIRS})
    MESSAGE ("SDL2 library path:" ${SDL2_ALL_LIBS_PATH}${SDL2_LIBRARY_NAME})
    MESSAGE ("SDL2 library path:" ${SDL2_ALL_LIBS_PATH}${SDL2_MAIN_LIBRARY_NAME})
endmacro ()
##########################################

##########################################
#             Call SDL2 macros           #
##########################################
add_and_link_sdl2()
##########################################

##########################################
#           Set target properties        #
##########################################
set_target_properties (atge PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
##########################################

##########################################
#               Run scripts              #
##########################################
execute_process (
    COMMAND go run ./scripts/copy_files.go WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
##########################################

##########################################
#          How to build and run          #
##########################################
# mkdir build
# cd build
# cmake ../CMake/
# cmake --build .
# cd Debug
# ./atge
##########################################