cmake_minimum_required(VERSION 3.0.0)

set(PROJECT globcpp)
set(CMAKE_CXX_STANDARD 14)

project(${PROJECT} VERSION 0.1.0)

find_package(Boost COMPONENTS filesystem regex)
include_directories(${Boost_INCLUDE_DIRS})
add_compile_definitions(BOOST_FILESYSTEM_NO_DEPRECATED)

enable_testing()
include(GoogleTest)
add_subdirectory(tests)

add_library(${PROJECT_NAME} src/Glob.cpp src/Glob.h)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_executable(main src/main.cpp)
target_link_libraries(main ${PROJECT_NAME})
