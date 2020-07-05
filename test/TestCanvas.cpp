#include <string>
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include "color.h"
#include "canvas.h"

using namespace raytracer_challenge;
using namespace std;

TEST_CASE("Creating Canvas") {
    float w = 10;
    float h = 20;
    Canvas c (w, h);
    REQUIRE(c.width == w);
    REQUIRE(c.height == h);
    for (int i = 0; i < w; i++){
        for (int j = 0; j < h; j++){
            REQUIRE(c.colors[j][i].R == 0); 
            REQUIRE(c.colors[j][i].G == 0); 
            REQUIRE(c.colors[j][i].B == 0);
        }
    }

}

TEST_CASE("Writing Pixel To Canvas") {
    float w = 10;
    float h = 20;
    Canvas c (w, h);
    Color red (1, 0, 0);
    c.writePixel(red, 2, 3);
    REQUIRE(c.colors[2][3].R == 1);
    REQUIRE(c.colors[2][3].G == 0);
    REQUIRE(c.colors[2][3].B == 0);
}

TEST_CASE("Canvas to PPM Simple Header") {
    float w = 5;
    float h = 3;
    Canvas c (w, h);
    stringstream expected_ss;
    expected_ss << "P3\n"<< w << " " << 3 << "\n255\n";
    auto ppm_str = c.toPpm();
    string result_token;
    string expected_token;
    stringstream result_ss (ppm_str);
    for (int i = 0; i < 3; i++ ){
        std::getline(result_ss, result_token, '\n');
        std::getline(expected_ss, expected_token, '\n');
        REQUIRE(expected_token.compare(result_token) == 0);
    }
    
}

TEST_CASE("Canvas splitting long line"){
    float w = 10;
    float h = 2;
    Canvas c (w, h);
    // initialize canvas
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++) {
            c.writePixel(Color(1, 0.8, 0.6), j, i);
        }
    auto ppm_str = c.toPpm();
    cout << ppm_str << "\n";
    std::string token;
    stringstream ss(ppm_str);
    while(std::getline(ss, token, '\n')) {
        REQUIRE(token.size() <= 70);
    }
}

TEST_CASE("Testing Matrices Invertability") {

}