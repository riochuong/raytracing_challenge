#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xmath.hpp>
#include <math.h>
#include "catch.hpp"
#include "matrix_transforms.h"
#include "data_types.h"
#include "raytracing_helpers.h"

using namespace xt;
using namespace raytracer_challenge;
using namespace raytracer_challenge::raytracing_helpers;

TEST_CASE("Translating a ray") {
    Ray r (Point(1, 2, 3), Vect(0, 1, 0));
    auto scalingMat = tf::translation(3, 4, 5);
    auto newRay = tf::transformRay(r, scalingMat);
    REQUIRE(newRay.point == Point(4, 6, 8));
    REQUIRE(newRay.vect == Vect(0, 1, 0));
}

TEST_CASE("Scaling a ray") {
    Ray r (Point(1, 2, 3), Vect(0, 1, 0));
    auto scalingMat = tf::scaling(2, 3, 4);
    auto newRay = tf::transformRay(r, scalingMat);
    REQUIRE(newRay.point == Point(2, 6, 12));
    REQUIRE(newRay.vect == Vect(0, 3, 0));
}

TEST_CASE("Intersecting a scaled sphere with a ray"){
    Ray r (Point(0, 0, -5), Vect(0, 0, 1));
    Sphere s;
    s.setTransform(tf::scaling(2, 2, 2));
    auto intersections = intersect(s, r);
    REQUIRE(intersections.size() == 2);
    REQUIRE(intersections[0].t == 3);
    REQUIRE(intersections[1].t == 7);
}

TEST_CASE("Intersecting a translated sphere with a ray"){
    Ray r (Point(0, 0, -5), Vect(0, 0, 1));
    Sphere s;
    s.setTransform(tf::translation(5, 0, 0));
    auto intersections = intersect(s, r);
    REQUIRE(intersections.size() == 0);
}


