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

TEST_CASE("Nomral at nonaxial point") {
    Sphere s;
    Point p (3*sqrt(3), 3*sqrt(3), 3*sqrt(3));
    auto normal_vect = s.getNormalAt(p);
    REQUIRE(normal_vect == normal_vect.normalize());
}

TEST_CASE("Nomral at on x axis") {
    Sphere s;
    Point p (1, 0, 0);
    auto normal_vect = s.getNormalAt(p);
    REQUIRE(normal_vect == Vect(1, 0, 0));
}

TEST_CASE("Computing normal on transformed sphere"){
    Sphere s;
    auto tf_mat = tf::chain_transforms(tf::scaling(1, 0.5, 1), 
                                       tf::rotation_z(M_PI / 5));
    s.setTransform(tf_mat);
    std::cout << "tf _mat:\n" << tf_mat << "\n";
    std::cout << "MPI: " << M_PI / 5<< "\n";
    auto normal_vect = s.getNormalAt(Point(0, sqrt(2)/2, -sqrt(2)/2));
    REQUIRE(Vect(0, 0.97014, -0.24254) == normal_vect);
}

TEST_CASE("Reflect 45deg slanted surface") {
    Vect v (0, -1, 0);
    Vect normal (sqrt(2)/2, sqrt(2)/2, 0);
    auto r_vect = reflect(v, normal);
    REQUIRE(xt::isclose(r_vect.x, 1.0)());
    REQUIRE(xt::isclose(r_vect.y, 0.0)());
    REQUIRE(xt::isclose(r_vect.z, 0.0)());
}
