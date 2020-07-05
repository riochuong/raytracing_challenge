#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "color.h"

using namespace std;
using namespace raytracer_challenge;

namespace raytracer_challenge {
    class Canvas {
        public:
            float width;
            float height;
            const uint32_t MAX_COLOR_VALUE = 255;
            const uint32_t MAX_CHAR_PER_PPM_LINE = 70;
            const std::string PPM_MAGIC_VALUE = "P3";
            vector<vector<Color>> colors;

        Canvas(float w, float h): width(w), height(h) {
            if ((width <= 0) || (height <=0)) {
                throw runtime_error{"Invalid width/height value !! Must be positive"}; 
            }
            for (int i = 0; i < h; i++){
                colors.push_back(vector<Color>());
                for (int j = 0; j < w; j++){
                    colors[i].push_back(Color());
                }
            }
        }

        /**
         *  @brief  write a specific color value to a specific canvas pixel
         *  @param Color: specifica Color value to be written
         *  @param int : row - row position of the pixel
         *  @param int: col - column position of the pixel
         *  @return  void
        */
        void writePixel(Color c, int row, int col);
        
        /**
         *  @brief  return a specific string describing canvas in ppm format
         *  @return  string: string represent ppm format 
        */
        std::string toPpm();
        
        private:
            /**
             *  @brief  append current pixel to string stream
             *  @param Color: specifica Color value to be written
             *  @param int : row - row position of the pixel
             *  @param int: col - column position of the pixel
             *  @param stringstream: ss - current string stream represent ppm data
             *  @param int: lineCount - number of char in current line
             *  @return  void
            */
            void appendPixelToPPMStream(uint32_t r, uint32_t c, stringstream &ss, uint32_t &lineCount);
    };


}