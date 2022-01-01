//
// Created by jeang on 2021-12-29.
//
#pragma once

#include "utils.h"
#include "ray.h"

class Camera{
public:
    Camera();
    Camera(Point3 look_from, Point3 look_at, Vec3 view_up, double vertical_field_of_view, double aspect_ratio);
    Camera(Point3 look_from, Point3 look_at, Vec3 view_up, double vertical_field_of_view, double aspect_ratio, double aperture, double focus_distance);

    Ray get_ray(double u, double v);

private:
    Point3 origin_;
    Vec3 horizontal_;
    Vec3 vertical_;
    Point3 lower_left_corner_;
    Vec3 w_, u_, v_;
    double lens_radius_;
};
