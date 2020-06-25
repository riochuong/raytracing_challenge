cmake_minimum_required(VERSION 3.14.3)

project(raytracer_challenge_test)
set (TARGET raytracer)

add_library(${TARGET} 
    SHARED
    color.cpp
    canvas.cpp
)