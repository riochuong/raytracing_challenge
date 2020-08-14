cmake_minimum_required(VERSION 3.14.3)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_REQUIRED_INCLUDES ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_BUILD_TYPE Debug)

project(RayTracerChallenge)

# adding xtensor to project
find_package(xtensor REQUIRED)
include_directories()

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include
)
message("CMAKE CXX COMPILER ${CMAKE_CXX_COMPILER}")

add_subdirectory(src)
add_subdirectory(test)

