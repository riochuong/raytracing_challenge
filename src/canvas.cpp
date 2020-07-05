#include <string>
#include <sstream>
#include <algorithm>
#include "canvas.h"
#include "utils.h"

using namespace std;

void Canvas::writePixel(Color c, int row, int col)
{
    if ((row < 0 || row >= this->height) || (col < 0 || col >= this->width))
    {
        throw runtime_error("Row index need to be valid positive number");
    }
    this->colors[row][col] = c;
}

void Canvas::appendPixelToPPMStream(uint32_t r, uint32_t c, stringstream &ss, uint32_t &lineCount) {
    vector<uint16_t> rgb;
    uint8_t num_digit = 0;
    rgb.push_back(clip<uint16_t>(this->colors[r][c].R * this->MAX_COLOR_VALUE, 0, this->MAX_COLOR_VALUE));
    rgb.push_back(clip<uint16_t>(this->colors[r][c].G * this->MAX_COLOR_VALUE, 0, this->MAX_COLOR_VALUE));
    rgb.push_back(clip<uint16_t>(this->colors[r][c].B * this->MAX_COLOR_VALUE, 0, this->MAX_COLOR_VALUE));

    for (uint16_t val : rgb) {
        // quick trick to count digit
        if (val >=0 && val < 10){
            num_digit = 1;
        }
        else if (val >= 10 && val < 100) {
            num_digit = 2;
        } else {
            num_digit = 3;
        }

        // now we can add pixel value depending on number of character
        if ((lineCount + num_digit + 1) >= this->MAX_CHAR_PER_PPM_LINE - 1) {
            ss << "\n";
            ss << val;
            ss << " ";
            lineCount = num_digit + 1;
        } else {
            ss << val;
            ss << " ";
            lineCount += num_digit + 1;
        }
    }
}

std::string Canvas::toPpm()
{
    stringstream ppm_ss;
    uint32_t char_count = 0;
    // HEADER
    ppm_ss << this->PPM_MAGIC_VALUE << "\n";
    ppm_ss << this->width << " " << this->height << "\n";
    ppm_ss << this->MAX_COLOR_VALUE << "\n";

    // PIXELS
    for (int i = 0; i < this->width; i++)
        for (int j = 0; j < this->height; j++)
        {
            appendPixelToPPMStream(j, i, ppm_ss, char_count);
        }

    // PPM required new line at the end
    ppm_ss << "\n";
    return ppm_ss.str();
}


