#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xmath.hpp>
#include "catch.hpp"
#include "matrix_transforms.h"
#include "data_types.h"
#include "raytracing_helpers.h"


using namespace xt;
using namespace raytracer_challenge;
using namespace raytracer_challenge::raytracing_helpers;

typedef xt::numeric_constants<double> numeric;

TEST_CASE("Computing point from a distance") {
    Ray r (Point(2, 3, 4), Vect(1, 0, 0));
    
    Point move1 = position(r, 0);
    Point expected_move1(2, 3, 4);
    REQUIRE(xt::allclose(move1.get_mat_data(), expected_move1.get_mat_data()));

    Point move2 = position(r, 1);
    Point expected_move2(3, 3, 4);
    REQUIRE(xt::allclose(move2.get_mat_data(), expected_move2.get_mat_data()));

    Point move3 = position(r, -1);
    Point expected_move3(1, 3, 4);
    REQUIRE(xt::allclose(move3.get_mat_data(), expected_move3.get_mat_data()));

    Point move4 = position(r, 2.5);
    Point expected_move4(4.5, 3, 4);
    REQUIRE(xt::allclose(move4.get_mat_data(), expected_move4.get_mat_data()));
}