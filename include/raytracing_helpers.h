#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include "color.h"
#include "data_types.h"

using namespace std;
using namespace xt;

namespace raytracer_challenge {
    namespace raytracing_helpers{
        /**
         *  @brief  compute point travel in t unit of time
         *  @param Ray: ray for applying position calculation
         *  @param double : t time unit
         *  @return  xarray: translation matrix
        */
        Point position(Ray r, double t);

        /**
         *  @brief  find intersects between sphere and ray 
         *  @param Ray: ray for applying position calculation
         *  @param Sphere : s sphere 
         *  @return  vector: intersect distances from ray origin (can be negatives)
        */
        vector<Intersection> intersect(Sphere s, Ray r);


         /**
         *  @brief  find intersection that is visible and infront of ray origin
         *  @param vector<Intersection>: list of intersections
         *  @return  int32_t index: index of the hit or -1 if no hit found
        */
        int32_t hit(const vector<Intersection> &intersections);
    }
}