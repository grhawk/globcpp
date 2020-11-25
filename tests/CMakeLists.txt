cmake_minimum_required(VERSION 3.0.0)

# Set the name of the parent project followed by `-tests`
project(${PROJECT_NAME}-tests VERSION 0.1.0)

configure_file(${CMAKE_SOURCE_DIR}/tests/gtest.cmake googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                EXCLUDE_FROM_ALL)

if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()


include_directories(${CMAKE_SOURCE_DIR}/src)


add_executable(${PROJECT_NAME} GlobTest.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main example)

gtest_discover_tests(${PROJECT_NAME})