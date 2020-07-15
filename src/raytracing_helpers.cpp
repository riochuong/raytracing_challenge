#include <string>
#include <sstream>
#include <algorithm>
#include <xtensor/xarray.hpp>
#include <xtensor/xmath.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <math.h>
#include "raytracing_helpers.h"
#include "matrix_transforms.h"

using namespace xt;

namespace raytracer_challenge
{
    namespace raytracing_helpers
    {

        Point position(Ray r, double t)
        {
            auto result = r.point.get_mat_data() + r.vect.get_mat_data() * t;
            return Point(result[{0, 0}], result[{1, 0}], result[{2, 0}]);
        }

        vector<Intersection> intersect(Sphere s, Ray r)
        {
            vector<Intersection> dists;
            
            auto rTransform = linalg::inv(s.getTransform());

            auto newRay = tf::transformRay(r, rTransform);

            auto sphere_to_ray = newRay.point.get_mat_data() - s.origin.get_mat_data();
            
            auto r_vect_mat = newRay.vect.get_mat_data();
            
            auto a = linalg::vdot(r_vect_mat, r_vect_mat);
            
            auto b = 2 * linalg::vdot(newRay.vect.get_mat_data(), sphere_to_ray);
            
            auto c = linalg::vdot(sphere_to_ray, sphere_to_ray) - 1;
            
            auto discriminant = b * b - 4 * a * c;

            // std::cout << "r.point\n" << r.point.get_mat_data() << "\n";
            // std::cout << "r.vect\n" << r.vect.get_mat_data() << "\n";
            // std::cout << "s.origin\n" << s.origin.get_mat_data() << "\n";
            // std:cout << "sphere_to_ray\n" << sphere_to_ray << "\n";
            // std::cout << "a\n" << a << "\n";
            // std::cout << "b\n" << b << "\n";
            // std::cout << "c\n" << c << "\n";
            // std::cout << "Discr\n" << discriminant << "\n";
            
            if (discriminant < 0)
            {
                // ray miss sphere_to_ray
                return dists;
            }
            else
            {
                dists.push_back(
                     Intersection((-b - sqrt(discriminant)) / (2 * a), s));
                dists.push_back(
                     Intersection((-b + sqrt(discriminant)) / (2 * a),s));
            }
            return dists;
        }

        int32_t hit(const vector<Intersection> &intersections) {
            int32_t hit_idx = -1;
            for(int i = 0; i < intersections.size(); i++){
                if ((intersections[i].t >= 0) && 
                        ((hit_idx < 0) || (intersections[hit_idx].t > intersections[i].t))) {
                    hit_idx = i;
                }
            }
            return hit_idx;
        }
    } // namespace raytracing_helpers
} // namespace raytracer_challenge
