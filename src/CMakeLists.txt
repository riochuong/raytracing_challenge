cmake_minimum_required(VERSION 3.14.3)

project(raytracer_challenge_test)
set (TARGET raytracer)

add_library(${TARGET} 
    SHARED
    canvas.cpp
    matrix_transforms.cpp
    raytracing_helpers.cpp
    data_types.cpp
)