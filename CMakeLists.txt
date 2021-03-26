cmake_minimum_required(VERSION 3.8)

project(atge)

set(EXE "./main.cpp")

set(LOGGING "./Utils/Include/ATLogger.hpp" "./Utils/Source/ATLogger.cpp")
set(OTHER "./Utils/Include/ATDefineExtensions.hpp")

set(UTILS ${LOGGING} ${MUTEX})

add_executable(main ${EXE} ${UTILS} ${OTHER})

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# cmake ../
# cmake --build .