//
// Created by jeang on 2022-01-01.
//

#pragma once

//#include <memory>
//#include <limits>
//#include <random>
#include <Eigen/Dense>
#include <fmt/core.h>


// vectors that will be used and related functions
using Vec3 = Eigen::Vector3d;
using Point3 = Eigen::Vector3d;
using Color = Eigen::Vector3d;

Vec3 unit_vector(const Vec3& v);

double dot(const Vec3& v1, const Vec3& v2);

Vec3 cross(const Vec3& v1, const Vec3& v2);

//inline Vec3 unit_vector(const Vec3& v){
//    return v.normalized();
//}
//
//inline double dot(const Vec3& v1, const Vec3& v2){
//    return v1.dot(v2);
//}
//
//inline Vec3 cross(const Vec3& v1, const Vec3& v2)
//{
//    return v1.cross(v2);
//}