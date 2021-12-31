//
// Created by jeang on 2021-12-29.
//
#pragma once

#include "utils.h"
#include "ray.h"

class Camera{
public:
    Camera();

    Ray get_ray(double u, double v);

private:
    Point3 origin_;
    Vec3 horizontal_;
    Vec3 vertical_;
    Point3 lower_left_corner_;
};
