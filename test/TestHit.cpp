#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xmath.hpp>
#include <math.h>
#include "catch.hpp"
#include "data_types.h"
#include "raytracing_helpers.h"

using namespace raytracer_challenge;
using namespace raytracer_challenge::raytracing_helpers;


TEST_CASE("All positive intersections"){
    vector<Intersection> intersections = {
        Intersection(1, Sphere()),
        Intersection(2, Sphere())
    };
    auto hit_idx = hit(intersections);
    REQUIRE(hit_idx == 0);
}


TEST_CASE("Some negative intersections"){
    vector<Intersection> intersections = {
        Intersection(-1, Sphere()),
        Intersection(2, Sphere())
    };
    auto hit_idx = hit(intersections);
    REQUIRE(hit_idx == 1);
}


TEST_CASE("all negative intersections"){
    vector<Intersection> intersections = {
        Intersection(-1, Sphere()),
        Intersection(-22, Sphere()),
        Intersection(-23, Sphere()),
        Intersection(-4, Sphere()),
    };
    auto hit_idx = hit(intersections);
    REQUIRE(hit_idx == -1);
}

TEST_CASE("loweset non-negative intersection for hit"){
    vector<Intersection> intersections = {
        Intersection(30, Sphere()),
        Intersection(22, Sphere()),
        Intersection(2, Sphere()),
        Intersection(4, Sphere()),
    };
    auto hit_idx = hit(intersections);
    REQUIRE(hit_idx == 2);
}