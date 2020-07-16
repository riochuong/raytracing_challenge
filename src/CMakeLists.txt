cmake_minimum_required(VERSION 3.14.3)

project(raytracer_challenge_test)
set (TARGET raytracer)
set (RAYSPHEREAPP ray_sphere_app)

add_library(${TARGET} 
    SHARED
    canvas.cpp
    matrix_transforms.cpp
    raytracing_helpers.cpp
    data_types.cpp
)

add_executable(
    ${RAYSPHEREAPP}
    raysphereapp.cpp
)

target_link_libraries(
    ${RAYSPHEREAPP}
    ${TARGET}
    lapack 
    blas
)