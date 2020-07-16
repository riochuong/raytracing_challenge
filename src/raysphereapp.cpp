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
    int numCanvasPixels = 400;
    double pixelSize = wallSize / numCanvasPixels;
    double halfWallSize = wallSize / 2.0;
    Sphere s;
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
            auto sphereTransform = tf::scaling(0.5, 1, 1);
            auto rayTf = tf::transformRay(Ray(rayOrigin, vect.normalize()), 
                                          xt::linalg::inv(sphereTransform));
            if (hit(intersect(s, rayTf)) >= 0) {

                canvas.writePixel(red, x, y);
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