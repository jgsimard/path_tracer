//
// Created by jeang on 2021-12-29.
//

#include "camera.h"
#include "vec.h"


Camera::Camera(){
    auto aspect_ratio = 16.0 / 9.0;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    origin_ = Point3(0, 0, 0);
    horizontal_ = Vec3(viewport_width, 0, 0);
    vertical_ = Vec3(0, viewport_height, 0);
    lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 - Vec3(0, 0, focal_length);
}

Camera::Camera(Point3 look_from, Point3 look_at, Vec3 view_up, double vertical_field_of_view, double aspect_ratio)
{
    double theta = degrees_to_radians(vertical_field_of_view);
    auto h = std::tan(theta * 0.5);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    // create an orthonormal basis for the camera
    auto w = unit_vector(look_from - look_at); // z
    auto u = unit_vector(cross(view_up, w)); // x
    auto v = cross(w, u); // y

    origin_ = look_from;
    horizontal_ = viewport_width * u;
    vertical_ = viewport_height * v;
    lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 -w;
}

Camera::Camera(
        Point3 look_from,
        Point3 look_at,
        Vec3 view_up,
        double vertical_field_of_view, // how many degrees the camera sees
        double aspect_ratio,
        double aperture, // size of the hole in the camera
        double focus_distance // distance between the camera and the lens
        )
{
    double theta = degrees_to_radians(vertical_field_of_view);
    auto h = std::tan(theta * 0.5);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

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

//Ray Camera::get_ray(double u, double v){
//    return Ray(origin_, lower_left_corner_ + u * horizontal_ + v * vertical_ - origin_);
//}


Ray Camera::get_ray(double u, double v){
    Vec3 direction = lens_radius_ * random_in_unit_disk();
    Vec3 offset = u_ * direction.x() + v_ * direction.y();
    return Ray(origin_ + offset, lower_left_corner_ + u * horizontal_ + v * vertical_ - origin_ - offset);
}

