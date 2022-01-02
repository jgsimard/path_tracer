//
// Created by jeang on 2021-12-28.
//

#include "utils.h"
#include "vec.h"

// Utility Functions
double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double radians_to_degrees(double radians) {
    return radians / pi * 180.0;
}

double random_double(){
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

void write_color(Color pixel_color) {
    // Write the translated [0,255] value of each color component.
    fmt::print("{0} {1} {2}\n",
               static_cast<int>(255.999 * pixel_color(0)),
               static_cast<int>(255.999 * pixel_color(1)),
               static_cast<int>(255.999 * pixel_color(2)));
}


void write_color(const Color pixel_color, const int samples_per_pixels) {
    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixels;
    Color pixel_color_adjusted = (pixel_color * scale).array().sqrt().matrix(); // sqrt for gamma correction

    // Write the translated [0,255] value of each color component.
    fmt::print("{0} {1} {2}\n",
               static_cast<int>(256 * std::clamp(pixel_color_adjusted.x(), 0.0, 0.999)),
               static_cast<int>(256 * std::clamp(pixel_color_adjusted.y(), 0.0, 0.999)),
               static_cast<int>(256 * std::clamp(pixel_color_adjusted.z(), 0.0, 0.999)));
}


//Vec3 random_vec(){
//    return ((Vec3::Random().array() + 1.0) / 2.0).matrix(); // the range of Random() is [-1, 1]
//}

Vec3 random_vec(){
    return Vec3::Random(); // the range of Random() is [-1, 1]
}

Vec3 random_vec(double min, double max){
    return ((Vec3::Random().array() + 1.0) * 0.5 * (max - min) + min).matrix();
}

//Vec3 random_vec(double min, double max){
//    return ((Vec3::Random().array() + 1.0) * 0.5 * (max - min) + min).matrix();
//}

Vec3 random_in_unit_sphere() {
    while (true) {
        auto v = Vec3::Random(); // the natural range is [-1, 1]
        if (v.squaredNorm() >= 1) continue;
        return v;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 random_in_hemisphere(const Vec3& normal) {
    Vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

bool near_zero(const Vec3& v)  {
    // Return true if the vector is close to zero in all dimensions.
//    const auto s = 1e-8;
//    return (fabs(v[0]) < s) && (fabs(v[1]) < s) && (fabs(v[2]) < s);
    const auto s = 1e-6;
    return v.squaredNorm() < s;
}

Vec3 reflect(const Vec3& v, const Vec3& normal)
{ // draw a picture to get it, pretty easy to understand
    return v - 2 * dot(v, normal) * normal;
}

Vec3 refract(const Vec3& v_in, const Vec3& normal, double ratio_index_of_refraction)
{
    double cos_theta = std::min(dot(-v_in, normal), 1.0);
    Vec3 v_out_perp = ratio_index_of_refraction * (v_in + cos_theta * normal );
    Vec3 v_out_parallel = -sqrt(std::abs(1- v_out_perp.squaredNorm())) * normal;
    return v_out_perp + v_out_parallel;
}

Vec3 random_in_unit_disk()
{
    while(true){
        auto v = random_vec();
        v.z() = 0.0;
        if (v.squaredNorm() >= 1.0) continue;
        return v;
    }
}

int random_int(int min, int max) {
    // TODO fix this
    // Returns a random integer in [min,max].
    static std::uniform_int_distribution<int> distribution_int(0, 2);
    static std::mt19937 generator_int;
    return distribution_int(generator_int);
}

