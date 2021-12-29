//
// Created by jeang on 2021-12-28.
//

#include "utils.h"

// Utility Functions
double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double random_double(){
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

void write_color(Color pixel_color) {
    // Write the translated [0,255] value of each color component.
    fmt::print("{0} {1} {2}\n",
               static_cast<int>(255.999 * pixel_color(0)),
               static_cast<int>(255.999 * pixel_color(1)),
               static_cast<int>(255.999 * pixel_color(2)));
}



void write_color(Color pixel_color, const int samples_per_pixels) {
    // TODO optimize this
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixels;
    r *= scale;
    g *= scale;
    b *= scale;

    // Write the translated [0,255] value of each color component.
    fmt::print("{0} {1} {2}\n",
               static_cast<int>(256 * std::clamp(r, 0.0, 0.999)),
               static_cast<int>(256 * std::clamp(g, 0.0, 0.999)),
               static_cast<int>(256 * std::clamp(b, 0.0, 0.999)));
}

Vec3 unit_vector(const Vec3& v){
    return v.normalized();
}