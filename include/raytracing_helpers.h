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
         *  @brief  create ray 
         *  @param Ray: ray for applying position calculation
         *  @param double : t position
         *  @return  xarray: translation matrix
        */
        Point position(Ray r, double t);
    }
}