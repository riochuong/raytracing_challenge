#include <iostream>
#include <fstream>
#include <xtensor/xarray.hpp>
#include <string>
#include "matrix_transforms.h"
#include "raytracing_helpers.h"
#include "data_types.h"
#include "canvas.h"

using namespace raytracer_challenge::raytracing_helpers;
using namespace raytracer_challenge;

int main (int argc, char** argv){
    Point rayOrigin (0, 0, -5);
    // z location of wall 
    double wallZ = 10;
    double wallSize = 7.0;
    int numCanvasPixels = 100;
    double pixelSize = wallSize / numCanvasPixels;
    double halfWallSize = wallSize / 2.0;
    Sphere s;
    s.material = Material();
    s.material.color = Color(1, 0.2, 1);

    // add light source 
    PointLight light(Point(20, 0, -10), Color(0.5, 0.5, 0.5));

    Color red(1, 0, 0);
    Canvas canvas (numCanvasPixels, numCanvasPixels);
    auto xs = xt::arange(0, numCanvasPixels);
    auto ys = xt::arange(0, numCanvasPixels);

    // convert pixels coords. to world coords
    auto worldY = halfWallSize -  ys * pixelSize;
    auto worldX = -halfWallSize + xs * pixelSize;
    for(int x = 0; x < worldX.shape()[0]; x++){
        for(int y = 0; y < worldY.shape()[0]; y++){
            Point pos (worldX[x], worldY[y], wallZ);
            Vect vect = pos - rayOrigin;
            auto sphereTransform = tf::scaling(1, 1, 1);
            auto rayTf = tf::transformRay(Ray(rayOrigin, vect.normalize()), 
                                          xt::linalg::inv(sphereTransform));
            
            auto intersects = intersect(s, rayTf);
            auto hit_idx = hit(intersects);
            if (hit_idx >= 0) {
                
                auto hit_obj = intersects[hit_idx];
                auto hit_point = position(rayTf, hit_obj.t);
                auto normal_at_hit_point = hit_obj.object.getNormalAt(hit_point);
                auto eye_vect = rayTf.vect * (-1);
                auto color = lighting(hit_obj.object.material, 
                                      light, hit_point, 
                                      eye_vect, 
                                      normal_at_hit_point);
                canvas.writePixel(color, x, y);
            }
        }
    }
    // write ppm to file
    std::string ppmStr = canvas.toPpm();
    std::ofstream of("sphere_and_ray.ppm");
    of << ppmStr;
    of.close();
    return 0;
}