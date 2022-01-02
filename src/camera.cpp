//
// Created by jeang on 2021-12-29.
//

#include "camera.h"
#include "vec.h"


Camera::Camera(){
    float aspect_ratio = 16.0 / 9.0;
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0f;

    lens_radius_ =0.0f;

    origin_ = Point3(0, 0, 0);
    horizontal_ = Vec3(viewport_width, 0, 0);
    vertical_ = Vec3(0, viewport_height, 0);
    lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 - Vec3(0, 0, focal_length);
}

Camera::Camera(const Point3& look_from, const Point3& look_at, const Vec3& view_up, float vertical_field_of_view, float aspect_ratio)
{
    float theta = degrees_to_radians(vertical_field_of_view);
    float h = std::tan(theta * 0.5f);
    float viewport_height = 2.0f * h;
    float viewport_width = aspect_ratio * viewport_height;

    lens_radius_ =0.0f;

    // create an orthonormal basis for the camera
    Vec3 w = unit_vector(look_from - look_at); // z
    Vec3 u = unit_vector(cross(view_up, w)); // x
    Vec3 v = cross(w, u); // y

    origin_ = look_from;
    horizontal_ = viewport_width * u;
    vertical_ = viewport_height * v;
    lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 -w;
}

Camera::Camera(
        const Point3& look_from,
        const Point3& look_at,
        const Vec3& view_up,
        float vertical_field_of_view, // how many degrees the camera sees
        float aspect_ratio,
        float aperture, // size of the hole in the camera
        float focus_distance // distance between the camera and the lens
        )
{
    float theta = degrees_to_radians(vertical_field_of_view);
    float h = std::tan(theta * 0.5f);
    float viewport_height = 2.0f * h;
    float viewport_width = aspect_ratio * viewport_height;

    // create an orthonormal basis for the camera
    w_ = unit_vector(look_from - look_at); // z
    u_ = unit_vector(cross(view_up, w_)); // x
    v_ = cross(w_, u_); // y

    origin_ = look_from;
    horizontal_ = focus_distance * viewport_width * u_;
    vertical_ = focus_distance * viewport_height * v_;
    lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 - focus_distance * w_;

    lens_radius_ = aperture / 2;
}


Ray Camera::get_ray(float u, float v){
    Vec3 direction = lens_radius_ * random_in_unit_disk();
    Vec3 offset = u_ * direction[0] + v_ * direction[1];
    return Ray(origin_ + offset, lower_left_corner_ + u * horizontal_ + v * vertical_ - origin_ - offset);
}

