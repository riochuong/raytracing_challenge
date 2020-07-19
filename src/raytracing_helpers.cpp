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

        Vect reflect(const Vect &in, const Vect &normal) {
            if (!xt::isclose(normal.getLength(), 1.0)()) {
                throw runtime_error("Normal vector must be a unit vector");
            }
            auto reflect = in.get_mat_data() - normal.get_mat_data() *  
                2 * linalg::vdot(in.get_mat_data() , normal.get_mat_data());
            return Vect(reflect[{0,0}], reflect[{1,0}], reflect[{2,0}]);
        }

         Color lighting(const Material &material, 
                       const PointLight &light,
                       const Point &position,
                       const Vect &eye_pos,
                       const Vect &normal_vect
                       ) {
            
            // default color is black 
            Color diffuse;
            Color specular;
            Color effective_color = material.color * light.intensity;
            // direction to light source
            Vect light_vect = (light.position - position).normalize();
            Color ambient = effective_color * material.ambient;

            // compute angle between light and surface normal 
            double light_dot_normal = linalg::vdot(light_vect.get_mat_data(), normal_vect.get_mat_data());

            // negative mean light source is behind
            if (light_dot_normal >= 0) {
                diffuse = Color(effective_color * material.diffuse  * light_dot_normal);
                // check angle with eye vector 
                Vect reflect_v = reflect(light_vect * (-1.), normal_vect);
                auto reflect_dot_eye = linalg::vdot(reflect_v.get_mat_data(), eye_pos.get_mat_data());
                if (reflect_dot_eye < 0) {
                    specular = Color();
                }else {
                    // compute specular contribution
                    auto factor = pow(reflect_dot_eye, material.shininess);
                    specular = light.intensity * material.specular * factor;
                }
            }

            return ambient + specular + diffuse;

        }

        
    } // namespace raytracing_helpers
} // namespace raytracer_challenge
