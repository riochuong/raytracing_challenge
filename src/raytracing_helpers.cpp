#include <string>
#include <sstream>
#include <algorithm>
#include "raytracing_helpers.h"

using namespace raytracer_challenge;

Point raytracing_helpers::position(Ray r, double t) {
    auto result = r.point.get_mat_data() + r.vect.get_mat_data() * t;
    return Point(result[{0,0}], result[{1,0}], result[{2,0}]); 
}