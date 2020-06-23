// Main entry for start running all tests

namespace raytracer_challenge {
    class Color {
        public:
            float R;
            float G;
            float B;

        Color(float r, float g, float b): R(r), G(g), B(b) {};

        Color(): R(0), G(0), B(0) {};

        Color &operator+(const Color &rhs) {
            Color new_color;
            new_color.R = this->R + rhs.R;
            new_color.G = this->G + rhs.G;
            new_color.B = this->B + rhs.B;
            return new_color;
        }

        Color &operator-(const Color &rhs) {
            Color new_color;
            new_color.R = this->R - rhs.R;
            new_color.G = this->G - rhs.G;
            new_color.B = this->B - rhs.B;
            return new_color;
        }

        Color &operator*(const Color &rhs) {
            Color new_color;
            new_color.R = this->R * rhs.R;
            new_color.G = this->G * rhs.G;
            new_color.B = this->B * rhs.B;
            return new_color;
        }

        Color &operator*(float scalar) {
            Color new_color;
            new_color.R = this->R * scalar;
            new_color.G = this->G * scalar;
            new_color.B = this->B * scalar;
            return new_color;
        }

    };


}