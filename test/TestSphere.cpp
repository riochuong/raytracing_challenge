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

typedef xt::numeric_constants<double> numeric;

TEST_CASE("Sphere Intersect Rays at Two points") {
    Ray r (Point(0, 0, -5), Vect(0, 0, 1));
    Sphere s;
    auto intersects = intersect(s, r);
    REQUIRE(intersects.size() == 2);
    vector<Intersection> expected = {Intersection(4.0, s), Intersection(6.0, s)};
    REQUIRE(abs(intersects[0].t - intersects[0].t) < 0.0001); 
    REQUIRE(intersects[0].object == expected[0].object);
    REQUIRE(intersects[1].object == expected[1].object);

}

TEST_CASE("Sphere Intersect Rays at same point") {
    Ray r (Point(0, 1, -5), Vect(0, 0, 1));
    Sphere s;
    auto intersects = intersect(s, r);
    REQUIRE(intersects.size() == 2);
    vector<Intersection> expected = {Intersection(5.0, s), Intersection(5.0, s)};
    REQUIRE(xt::allclose(intersects[0].t, expected[0].t)); 
    REQUIRE(intersects[0].object == expected[0].object);
    REQUIRE(intersects[1].object == expected[1].object); 
}

TEST_CASE("Ray misses sphere") {
    Ray r (Point(0, 2, -5), Vect(0, 0, 1));
    Sphere s;
    auto intersects = intersect(s, r);
    REQUIRE(intersects.size() == 0);
}

TEST_CASE("Ray originates inside a sphere") {
    Ray r (Point(0, 0, 0), Vect(0, 0, 1));
    Sphere s;
    auto intersects = intersect(s, r);
    REQUIRE(intersects.size() == 2);
    vector<Intersection> expected = {Intersection(-1.0,s), Intersection(1.0,s)};
    REQUIRE(xt::allclose(intersects[0].t, expected[0].t)); 
    REQUIRE(intersects[0].object == expected[0].object);
    REQUIRE(intersects[1].object == expected[1].object);
}

TEST_CASE("Ray originates infront of a sphere") {
    Ray r (Point(0, 0, 5), Vect(0, 0, 1));
    Sphere s;
    auto intersects = intersect(s, r);
    REQUIRE(intersects.size() == 2);
    vector<Intersection> expected = {Intersection(-6.0, s), Intersection(-4.0, s)};
    REQUIRE(xt::allclose(intersects[0].t, expected[0].t)); 
    REQUIRE(intersects[0].object == expected[0].object);
    REQUIRE(intersects[1].object == expected[1].object);
}