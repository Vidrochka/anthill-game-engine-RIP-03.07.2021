# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("anthill-game-engine")

add_subdirectory (anthill-game-engine-utils)
add_subdirectory (anthill-game-engine-core)

add_subdirectory (anthill-game-engine)

execute_process (
    COMMAND go run ./scripts/copy_files.go WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

#target_link_libraries(anthill-game-engine anthill-game-engine-utils)