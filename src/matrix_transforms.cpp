#include "matrix_transforms.h"

using namespace raytracer_challenge;


xarray<double> tf::translation(double x, double y, double z)
{
    xarray<double> tmat = {
        {1, 0, 0, x},
        {0, 1, 0, y},
        {0, 0, 1, z},
        {0, 0, 0, 1},
    };
    return tmat;
}

xarray<double> tf::scaling(double x, double y, double z)
{
    xarray<double> tmat = {
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1},
    };
    return tmat;
}

xarray<double> tf::rotation_x(double theta)
{
    xarray<double> tmat = {
        {1, 0, 0, 0},
        {0, cos(theta), -sin(theta), 0},
        {0, sin(theta), cos(theta), 0},
        {0, 0, 0, 1},
    };
    return tmat;
}

xarray<double> tf::rotation_y(double theta)
{
    xarray<double> tmat = {
        {cos(theta), 0, sin(theta), 0},
        {0, 1, 0, 0},
        {-sin(theta), 0, cos(theta), 0},
        {0, 0, 0, 1},
    };
    return tmat;
}
xarray<double> tf::rotation_z(double theta)
{
    xarray<double> tmat = {
        {cos(theta), -sin(theta), 0, 0},
        {sin(theta), cos(theta), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
    return tmat;
}

xarray<double> tf::shearing(double x_y,
                        double x_z,
                        double y_x,
                        double y_z,
                        double z_x,
                        double z_y)
{
    xarray<double> tmat = {
        {1, x_y, x_z, 0},
        {y_x, 1, y_z, 0},
        {z_x, z_y, 1, 0},
        {0, 0, 0, 1},
    };
    return tmat;
}

Ray tf::transformRay(const Ray &ray, xarray<double> tf_mat) {
    if (tf_mat.shape().size() != 2 || 
        tf_mat.shape()[0] != 4 || 
        tf_mat.shape()[1] != 4) {
        throw runtime_error("transform matrix need to be 4x4");
    }
    Point p(ray.point);
    p.apply_transform(tf_mat);
    Vect v(ray.vect);
    v.apply_transform(tf_mat);
    return Ray(p, v);
}

