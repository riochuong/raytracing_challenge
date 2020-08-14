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

TEST_CASE("Point eye between light and wall test ") {
    Vect eye (0, 0, -1);
    Vect normal(0, 0, -1);
    Point position(0, 0, 0);
    Material m;
    PointLight light (Point(0, 0, -10), Color(1, 1, 1));
    Color result = lighting(m, light, position, eye, normal);
    REQUIRE(xt::isclose(result.R, 1.9)());
    REQUIRE(xt::isclose(result.G, 1.9)());
    REQUIRE(xt::isclose(result.B, 1.9)());
}


TEST_CASE("Point light eye move 45deg ") {
    Vect eye (0, sqrt(2)/2, sqrt(2)/2);
    Vect normal(0, 0, -1);
    Point position(0, 0, 0);
    Material m;
    PointLight light (Point(0, 0, -10), Color(1, 1, 1));
    // specular should fall off to 0 
    Color result = lighting(m, light, position, eye, normal);
    REQUIRE(xt::isclose(result.R, 1.0)());
    REQUIRE(xt::isclose(result.G, 1.0)());
    REQUIRE(xt::isclose(result.B, 1.0)());
}


TEST_CASE("Point light move 45deg ") {
    Vect eye (0, sqrt(2)/2, sqrt(2)/2);
    Vect normal(0, 0, -1);
    Point position(0, 0, 0);
    Material m;
    PointLight light (Point(0, 10, -10), Color(1, 1, 1));
    // specular should fall off to 0 
    Color result = lighting(m, light, position, eye, normal);
    REQUIRE(xt::isclose(result.R, 0.7364)());
    REQUIRE(xt::isclose(result.G, 0.7364)());
    REQUIRE(xt::isclose(result.B, 0.7364)());
}

TEST_CASE("Point light with eye on the path of the reflection vector ") {
    Vect eye (0, -sqrt(2)/2, -sqrt(2)/2);
    Vect normal(0, 0, -1);
    Point position(0, 0, 0);
    Material m;
    PointLight light (Point(0, 10, -10), Color(1, 1, 1));
    // specular should fall off to 0 
    Color result = lighting(m, light, position, eye, normal);
    REQUIRE(xt::isclose(result.R, 1.6364)());
    REQUIRE(xt::isclose(result.G, 1.6364)());
    REQUIRE(xt::isclose(result.B, 1.6364)());
}

TEST_CASE("Light source behind surfaces ") {
    Vect eye (0, 0, -1);
    Vect normal(0, 0, -1);
    Point position(0, 0, 0);
    Material m;
    PointLight light (Point(0, 0, 10), Color(1, 1, 1));
    // specular should fall off to 0 
    Color result = lighting(m, light, position, eye, normal);
    REQUIRE(xt::isclose(result.R, 0.1)());
    REQUIRE(xt::isclose(result.G, 0.1)());
    REQUIRE(xt::isclose(result.B, 0.1)());
}

TEST_CASE("World Ray Intersection") {
    World default_world = World::createDefaultWorld();
    Ray ray (Point(0, 0, -5), Vect(0, 0, 1));
    vector<Intersection> intersections = intersectWorld(ray, default_world);
    vector<double> expected_ts = {4, 4.5, 5.5, 6};
    REQUIRE(intersections.size() == expected_ts.size());
    for (int i =0; i < expected_ts.size(); i++){
        std::cout << "result " << intersections[i].t << "\n expected: " <<  expected_ts[i] << "\n";
        REQUIRE(xt::isclose(intersections[i].t, expected_ts[i])());
    }
}
