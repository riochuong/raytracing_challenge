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

         /**
         *  @brief  
         *  @param Material: material
         *  @param PointLight: light source
         *  @param Point position: position of the point being illuminated
         *  @param Point eye_pos: position of the eye
         *  @param Vect: normal vector
         *  @return  Color color: color 
        */
        Color lighting(const Material &material, 
                       const PointLight &light,
                       const Point &position,
                       const Vect &eye_pos,
                       const Vect &normal_vect
                       );

         /**
         *  @brief  Find reflect vector 
         *  @param Vect: input light vector
         *  @param Vect vector normal of surface
         *  @return  Color color: color 
        */
        Vect reflect(const Vect &in, const Vect &norm);
    }
}