cmake_minimum_required(VERSION 3.0.0)

set(PROJECT example1)

project(${PROJECT} VERSION 0.1.0)

find_package(Boost COMPONENTS filesystem regex)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()
include(GoogleTest)
add_subdirectory(tests)

add_library(example src/Glob.cpp src/Glob.h)
#target_link_libraries(example ${Boost_LIBRARY_DIRS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_executable(main src/main.cpp)
target_link_libraries(main example ${Boost_LIBRARY_DIRS})
