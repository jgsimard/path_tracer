//
// Created by jeang on 2021-12-28.
//

#include "utils.h"
#include "vec.h"

// Utility Functions
float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0f;
}

float radians_to_degrees(float radians) {
    return radians / pi * 180.0f;
}

float  random_double (){
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

void write_color(const Color& pixel_color) {
    // Write the translated [0,255] value of each color component.
    fmt::print("{0} {1} {2}\n",
               static_cast<int>(255.999 * pixel_color[0]),
               static_cast<int>(255.999 * pixel_color[1]),
               static_cast<int>(255.999 * pixel_color[2]));
}


void write_color(const Color& pixel_color, const int samples_per_pixels) {
    // Divide the color by the number of samples.
    float scale = 1.0f / samples_per_pixels;
    // sqrt for gamma correction
    Color pixel_color_adjusted = sqrt(pixel_color * scale); // linalg

    // Write the translated [0,255] value of each color component.
//    fmt::print("{0} {1} {2}\n",
//               static_cast<int>(256.0f * std::clamp(pixel_color_adjusted.x(), 0.0f, 0.999f)),
//               static_cast<int>(256.0f * std::clamp(pixel_color_adjusted.y(), 0.0f, 0.999f)),
//               static_cast<int>(256.0f * std::clamp(pixel_color_adjusted.z(), 0.0f, 0.999f)));
    fmt::print("{0} {1} {2}\n",
               static_cast<int>(256.0f * std::clamp(pixel_color_adjusted[0], 0.0f, 0.999f)),
               static_cast<int>(256.0f * std::clamp(pixel_color_adjusted[1], 0.0f, 0.999f)),
               static_cast<int>(256.0f * std::clamp(pixel_color_adjusted[2], 0.0f, 0.999f)));
}


//Vec3 random_vec(){
//    return ((Vec3::Random().array() + 1.0) / 2.0).matrix(); // the range of Random() is [-1, 1]
//}

Vec3 random_vec(){
    return random_vec01(); // the range of Random() is [-1, 1]
}

Vec3 random_vec01(){
    return Vec3(random_double(), random_double(), random_double());
//    return ((Vec3::Random().array() + 1.0) * 0.5 * (max - min) + min).matrix();
}

Vec3 random_vec(float  min, float  max){
    return random_vec01() * (max - min) + min;
//    return ((Vec3::Random().array() + 1.0) * 0.5 * (max - min) + min).matrix();
}

Vec3 random_in_unit_sphere() {
    while (true) {
        Vec3 v = random_vec01() * 2.0f - 1.0f; // the natural range is [-1, 1]
        if (length2(v) >= 1) continue;
        return v;
//        auto v = Vec3::Random(); // the natural range is [-1, 1]
//        if (v.squaredNorm() >= 1) continue;
//        return v;
    }
}

Vec3 random_unit_vector() {
    // http://corysimon.github.io/articles/uniformdistn-on-sphere/
//    float theta = 2 * pi * random_double();
    float theta = pi2 * random_double();
    float phi = acos(1 - 2 * random_double());
    return Vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
//    return unit_vector(random_in_unit_sphere());
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
//    return v.squaredNorm() < s;
    return length2(v) < s;
}

Vec3 reflect(const Vec3& v, const Vec3& normal)
{ // draw a picture to get it, pretty easy to understand
    return v - 2 * dot(v, normal) * normal;
}

Vec3 refract(const Vec3& v_in, const Vec3& normal, float ratio_index_of_refraction)
{
    float  cos_theta = std::min(dot(-v_in, normal), 1.0f);
    Vec3 v_out_perp = ratio_index_of_refraction * (v_in + cos_theta * normal );
//    Vec3 v_out_parallel = -sqrt(std::abs(1- v_out_perp.squaredNorm())) * normal;
    Vec3 v_out_parallel = -sqrt(std::abs(1- length2(v_out_perp))) * normal;
    return v_out_perp + v_out_parallel;
}

Vec3 random_in_unit_disk()
{
//    float theta = 2 * pi * random_double();
    float theta = pi2  * random_double();
    float r_sqrt = sqrt(random_double());
    return Vec3(r_sqrt * cos(theta), r_sqrt * sin(theta), 0.0f);

//    while(true){
//        auto v = random_vec();
//        v.z() = 0.0f;
//        if (v.squaredNorm() >= 1.0f) continue;
//        return v;
//    }
}

int random_int(int min, int max) {
    // TODO fix this
    // Returns a random integer in [min,max].
    static std::uniform_int_distribution<int> distribution_int(0, 2);
    static std::mt19937 generator_int;
    return distribution_int(generator_int);
}

