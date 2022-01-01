//
// Created by jeang on 2021-12-28.
//
#pragma once

// C++
#include <memory>
#include <limits>
#include <random>

// Eigen : matrix math
#include <Eigen/Dense>

// fast IO
#include <fmt/core.h>

//ME
#include "vec.h"


// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589793;

// Utility Functions
double degrees_to_radians(double degrees);
double radians_to_degrees(double radians);

double random_double();


//inline std::ostream& operator<<(std::ostream &out, const Vec3 &v);

void write_color(Color pixel_color);

void write_color(Color pixel_color, int samples_per_pixels);

Vec3 random_vec();

Vec3 random_vec(double min, double max);

Vec3 random_in_unit_sphere();

Vec3 random_unit_vector();

Vec3 random_in_hemisphere(const Vec3& normal);

bool near_zero(const Vec3& v);

Vec3 reflect(const Vec3& v, const Vec3& normal);

Vec3 refract(const Vec3& v_in, const Vec3& normal, double ratio_index_of_refraction);

Vec3 random_in_unit_disk();

