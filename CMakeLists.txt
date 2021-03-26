cmake_minimum_required(VERSION 3.8)

project(atge)

set(EXE "./main.cpp")

set(LOGGING "./Utils/Logger/ATLogger.hpp" "./Utils/Logger/ATLogger.cpp" "./Utils/Logger/ATLoggerDefineExtensions.hpp")

set(UTILS "./Utils/Utils.hpp" ${LOGGING})

add_executable(main ${EXE} ${UTILS})

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# cmake ../
# cmake --build .