#pragma once
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>

template<typename T>
bool isMatrixInvertible(const xt::xarray<T> &mat) {
    return xt::linalg::det(mat) != 0;
}

