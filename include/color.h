// Main entry for start running all tests
#pragma once

namespace raytracer_challenge {
    class Color {
        public:
            float R;
            float G;
            float B;

        constexpr Color(float r, float g, float b): R(r), G(g), B(b) {};

        constexpr Color(): R(0), G(0), B(0) {};

        constexpr Color(const Color &rhs): R(rhs.R),  G(rhs.G), B(rhs.B) {}

        constexpr Color operator+(const Color &rhs) const {
            Color new_color;
            new_color.R = this->R + rhs.R;
            new_color.G = this->G + rhs.G;
            new_color.B = this->B + rhs.B;
            return new_color;
        }

        constexpr Color operator-(const Color &rhs) const {
            Color new_color;
            new_color.R = this->R - rhs.R;
            new_color.G = this->G - rhs.G;
            new_color.B = this->B - rhs.B;
            return new_color;
        }

        constexpr Color operator*(const Color &rhs) const {
            Color new_color;
            new_color.R = this->R * rhs.R;
            new_color.G = this->G * rhs.G;
            new_color.B = this->B * rhs.B;
            return new_color;
        }

        constexpr Color operator*(float scalar) const {
            Color new_color;
            new_color.R = this->R * scalar;
            new_color.G = this->G * scalar;
            new_color.B = this->B * scalar;
            return new_color;
        }

        constexpr Color &operator=(const Color &rhs) {
            this->R = rhs.R;
            this->G = rhs.G;
            this->B = rhs.B;
            return *this;
        }

    };


}