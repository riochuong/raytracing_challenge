#pragma once
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include "data_types.h"

using namespace xt;
using namespace raytracer_challenge;

namespace raytracer_challenge
{
    namespace tf
    {
        template <typename T>
        bool isMatrixInvertible(const xt::xarray<T> &mat);

        /**
 *  @brief  create translation matrix from given x,y,z position
 *  @param double: x position
 *  @param double : y position
 *  @param double: z position
 *  @return  xarray: translation matrix
*/
        xarray<double> translation(double x, double y, double z);

        /**
 *  @brief  create translation matrix from given x,y,z position
 *  @param double: x position
 *  @param double : y position
 *  @param double: z position
 *  @return  xarray: translation matrix
*/
        xarray<double> scaling(double x, double y, double z);

        /**
 *  @brief  create rotation matrix around x_axis
 *  @param double: theta in radians
 *  @return  xarray: translation matrix
*/
        xarray<double> rotation_x(double theta);

        /**
 *  @brief  create rotation matrix around y_axis
 *  @param double: theta in radians
 *  @return  xarray: translation matrix
*/
        xarray<double> rotation_y(double theta);

        /**
 *  @brief  create rotation matrix around y_axis
 *  @param double: theta in radians
 *  @return  xarray: translation matrix
*/
        xarray<double> rotation_z(double theta);

        /**
 *  @brief  create rotation matrix around y_axis
 *  @param double: theta in radians
 *  @return  xarray: translation matrix
*/
        xarray<double> shearing(double x_y,
                                double x_z,
                                double y_x,
                                double y_z,
                                double z_x,
                                double z_y);

        template <typename T>
        T chain_transforms(T &t)
        {
            return t;
        }

        template <typename T, typename... Ts>
        T chain_transforms(T first, Ts... tfs)
        {
            return linalg::dot(first, chain_transforms(tfs...));
        }

        template <typename T>
        bool isMatrixInvertible(const xt::xarray<T> &mat)
        {
            return xt::linalg::det(mat) != 0;
        }

        Ray transformRay(const Ray &ray, xarray<double> tf_mat);

    } // namespace tf
} // namespace raytracer_challenge