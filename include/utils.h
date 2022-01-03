//
// Created by jeang on 2021-12-28.
//
#pragma once

// C++
#include <memory>
#include <limits>
#include <random>

// fast IO
#include <fmt/core.h>

// rng
#include "pcg32.h"
//#include "pcg32_8.h"

//ME
#include "vec.h"
#include "ray.h"


// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;
using std::sin;
using std::cos;
using std::acos;

// Constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.141592653589793f;
constexpr float pi2 = 2 * 3.141592653589793f;

// Utility Functions
float degrees_to_radians(float degrees);
float radians_to_degrees(float radians);

float random_double();

void write_color(const Color& pixel_color);

void write_color(const Color& pixel_color, int samples_per_pixels);

Vec3 random_vec();

Vec3 random_vec01();

Vec3 random_vec(float min, float max);

Vec3 random_in_unit_sphere();

Vec3 random_unit_vector();

Vec3 random_in_hemisphere(const Vec3& normal);

bool near_zero(const Vec3& v);

Vec3 reflect(const Vec3& v, const Vec3& normal);

Vec3 refract(const Vec3& v_in, const Vec3& normal, float ratio_index_of_refraction);

Vec3 random_in_unit_disk();

int random_int_0_2();


