#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "color.h"

using namespace raytracer_challenge;
 
TEST_CASE("Adding Colors") {
    Color c1(0.9, 0.6, 0.75);
    Color c2(0.7, 0.1, 0.25);
    Color c3 = c1 + c2;
    REQUIRE((c3.R - 1.6f) < 0.00001);
    REQUIRE((c3.G - 0.7f) < 0.00001);
    REQUIRE((c3.B - 1.0f) < 0.00001);
}


