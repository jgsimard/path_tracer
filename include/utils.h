//
// Created by jeang on 2021-12-28.
//

#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

// C++
#include <iostream>
#include <memory>
#include <limits>
#include <random>

// Eigen : matrix math
#include <Eigen/Dense>

// fast IO
#include <fmt/core.h>


// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = std::acos(-1);

// Utility Functions
double degrees_to_radians(double degrees);

double random_double();

// vectors that will be used and related functions
using Vec3 = Eigen::Vector3d;
using Point3 = Eigen::Vector3d;
using Color = Eigen::Vector3d;

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v);

void write_color(Color pixel_color);

void write_color(Color pixel_color, const int samples_per_pixels);

Vec3 unit_vector(const Vec3& v);

#endif //GRAPHICS_UTILS_H
