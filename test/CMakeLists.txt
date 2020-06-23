cmake_minimum_required(VERSION 3.14.3)
project(raytracer_challenge_test)

find_package(xtensor REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_REQUIRED_FLAGS -Wall)                   

add_library(Catch2 INTERFACE)

target_include_directories(Catch2
    INTERFACE ${CMAKE_SOURCE_DIR}/dep/catch2
)

set (UNIT_TEST_FILES 
    ${CMAKE_SOURCE_DIR}/test/TestColorData.cpp
)

set (TARGET_NAME unit_tests)

add_executable(${TARGET_NAME}
    ${UNIT_TEST_FILES}
)
message("UNIT TEST FILES ${UNIT_TEST_FILES}")

target_link_libraries(${TARGET_NAME} Catch2)



