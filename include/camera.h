//
// Created by jeang on 2021-12-29.
//
#pragma once

#include "utils.h"
#include "ray.h"

class Camera{
public:
    Camera();
    Camera(const Point3& look_from, const Point3& look_at, const Point3& view_up, float vertical_field_of_view, float aspect_ratio);
    Camera(const Point3& look_from, const Point3& look_at, const Point3& view_up, float vertical_field_of_view, float aspect_ratio, float aperture, float focus_distance);

    Ray get_ray(float u, float v);

private:
    Point3 origin_;
    Vec3 horizontal_;
    Vec3 vertical_;
    Point3 lower_left_corner_;
    Vec3 w_, u_, v_;
    float lens_radius_;
};
