//
// Created by jeang on 2021-12-29.
//

#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

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

#endif //GRAPHICS_CAMERA_H
