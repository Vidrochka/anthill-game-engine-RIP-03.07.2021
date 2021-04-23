cmake_minimum_required (VERSION 3.8)

add_executable (anthill-game-engine "anthill-game-engine.cpp" "anthill-game-engine.hpp")

target_link_libraries(anthill-game-engine anthill-game-engine-core)
#target_link_libraries(anthill-game-engine "../anthill-game-engine-utils")

include_directories("../third-party-libs/boost_1_75_0/")

set_target_properties (anthill-game-engine PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)