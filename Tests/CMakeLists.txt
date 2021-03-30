cmake_minimum_required(VERSION 3.8)

project(atge)

set (TESTS_SOURCES
	"./test.cpp")

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set (TEST test_atge)

add_executable (${TEST} ${TESTS_SOURCES})

target_link_libraries (${TEST} ${PROJECT} ${Boost_LIBRARIES})

enable_testing()

add_test (${TEST} ${TEST})

#add_executable(test_cases )

#target_link_libraries(test_cases ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

#add_test(NAME test1 COMMAND test_cases)

#set_target_properties(main PROPERTIES
    #CXX_STANDARD 20
    #CXX_STANDARD_REQUIRED YES
    #CXX_EXTENSIONS NO
#)