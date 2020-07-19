#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xmath.hpp>
#include "catch.hpp"
#include "matrix_transforms.h"
#include "data_types.h"

using namespace xt;
using namespace raytracer_challenge;

typedef xt::numeric_constants<double> numeric;

TEST_CASE("Vector normalize"){
    Vect v (1, 2, 3);
    Vect norm = v.normalize();
    REQUIRE(xt::isclose(norm.x, 0.26726)());
    REQUIRE(xt::isclose(norm.y, 0.53452)());
    REQUIRE(xt::isclose(norm.z, 0.80178)());
}

TEST_CASE("Multiply Matrices") {
    xarray<int> mat1 = {
        {1, 2,  3,  4},
        {5, 6,  7,  8},
        {9, 8,  7,  6},
        {5, 4,  3,  2}
    };
    xarray<int> mat2 = {
        {-2, 1,  2,  3},
        {3,  2,  1,  -1},
        {4,  3,  6,  5},
        {1,  2,  7,  8}
    };
    auto res = xt::linalg::dot(mat1, mat2);
    xarray<int> expected = {
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}
    };
    auto zero = xt::sum(res - expected)();
    std::cout << zero << "\n";
    REQUIRE( zero == 0);
}

TEST_CASE("Matrix multiply a tuple") {
    xarray<int> b {
        {1,2,3,1}
    };
    xarray<int> A {
        {1,2,3,4},
        {2,4,4,2},
        {8,6,4,1},
        {0,0,0,1}
    };
    b.reshape({4,1});
    auto result = xt::linalg::dot(A, b);
    xarray<int> expected_result = {
        {18, 24, 33, 1}
    };
    std::cout << "result shape: " << result.shape()[0] << " " << result.shape()[1] << "\n";
    REQUIRE(xt::sum(expected_result - result)() == 0);
}

TEST_CASE("Test Matrix Invertibility") {
    xarray<double> A {
        {6.,4.,4.,4.},
        {5.,5.,7.,6.},
        {4.,-9.,3.,-7.},
        {9,1.,7.,-6.}
    };
    REQUIRE(tf::isMatrixInvertible(A));

    A = {
        {-4, 2, -2, 3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0}
    };
    REQUIRE(!tf::isMatrixInvertible(A));
}

TEST_CASE("Invert a matrix ") {
    xarray<double> A {
        {-5., 2., 6., -8},
        {1., -5., 1., 8.},
        {7., 7., -6., -7.},
        {1., -3., 7, 4}
    };
    auto A_inv = linalg::inv(A);
    xarray<double> A_inv_exp = {
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.8139, -0.30075, 0.30639}
    };
    std::cout << "Expected:  " << "\n" << A_inv_exp << "\n";
    std::cout << "Result:  " << "\n" << A_inv << "\n";
    REQUIRE(xt::allclose(A_inv, A_inv_exp, 1e-04));

    // inverse multiplication 
    xarray<double> B {
        {1., 2., 3., 4.},
        {1., 5., 3., -1.},
        {1., 2., 6., 4.},
        {1., 8., 3., 9.}
    };
    auto prod_B_A = linalg::dot(B, A);
    auto like_B = linalg::dot(prod_B_A, A_inv);
    std::cout << "B : " << B << "\n";
    std::cout << "Like B: " << like_B << "\n";
    REQUIRE(xt::allclose(B, like_B, 1e-04));
}

TEST_CASE("Point Transformation") {
    xarray<double> point = {
        {-3, 4, 5, 1}
    };
    point.reshape({4, 1});
    auto tmat = tf::translation(5, -3, 2);
    auto result = linalg::dot(tmat, point);
    xarray<double> expected = {
        {2, 1, 7, 1}
    };
    expected.reshape({4, 1});
    std::cout << "Point transformed: " << result << "\n";
    std::cout << "Point expecteed:" << expected << "\n";
    REQUIRE(xt::allclose(expected, result));

}

TEST_CASE("Vector Transformation") {
    Vect vect (-3., 4., 5.);
    auto tmat = tf::translation(5, -3, 2);
    auto result = linalg::dot(tmat, vect.get_mat_homo_data());
    xarray<double> expected = {
        {-3, 4, 5, 0}
    };
    expected.reshape({4, 1});
    std::cout << "Vector transformed: " << result << "\n";
    std::cout << "Vector expecteed:" << expected << "\n";
    REQUIRE(xt::allclose(expected, result));

}

TEST_CASE("Individual Transformations and Chained ") {
    Point p (1, 0, 1);
    p.apply_transform(tf::rotation_x(numeric::PI_2));
    Point expected_point(1, -1, 0);
    REQUIRE(xt::allclose(expected_point.get_mat_data(), p.get_mat_data()));
    
    p.apply_transform(tf::scaling(5, 5, 5));
    expected_point = Point(5, -5, 0);
    std::cout << "p " << p.x << ' ' << p.y << ' ' << p.z << "\n";
    REQUIRE(xt::allclose(expected_point.get_mat_data(), p.get_mat_data()));
    
    p.apply_transform(tf::translation(10, 5, 7)); 
    expected_point = Point(15, 0, 7);
    REQUIRE(xt::allclose(expected_point.get_mat_data(), p.get_mat_data()));

    Point p_chain (1, 0 ,1);
    auto transforms = tf::chain_transforms(tf::translation(10, 5, 7), 
                                       tf::scaling(5, 5, 5),
                                       tf::rotation_x(numeric::PI_2));
    p_chain.apply_transform(transforms);
    REQUIRE(xt::allclose(p_chain.get_mat_data(), p.get_mat_data()));

    // chain transforms


}