//
// Created by jeang on 2021-12-28.
//

#include "sphere.h"

bool Sphere::hit(const Ray &ray, float  t_min, float  t_max, HitRecord& hit_record) const
{
    // this code solve the quadratic equation a x^2 + b x + c = 0
    // where a = dot(ray.direction(), ray.direction()), but ray.direction() is a unit vector so a=1 by construction.
    // so we remove it from the computation

    Vec3 oc = ray.origin() - center_;
//    float  a = dot(ray.direction(), ray.direction()); // =1 by definition
    float  half_b = dot(oc, ray.direction()); // using half_b results in less computation for the same retults
//    float  c = dot(oc, oc) - radius_*radius_;
    float  c = dot(oc, oc) - radius_square_;
//    float  discriminant = half_b * half_b - a * c;
    float  discriminant = half_b * half_b - c; // a=1 by construction
    if (discriminant < 0) // does not touch
        return false;

    // Find the nearest root that lies in the acceptable range.
    float  sqrt_discriminant = std::sqrt(discriminant);
//    float  root = (-half_b - sqrt_discriminant) / a ;// find closest root
    float  root = (-half_b - sqrt_discriminant)  ;// find closest root
    if ((root < t_min) || (root > t_max)){ // check if outside range
//        root = (-half_b + sqrt_discriminant) / a ;
        root = (-half_b + sqrt_discriminant) ;
        if ((root < t_min) || (root > t_max))
            return false;
    }

    // update the hit_record
    hit_record.t = root;
    hit_record.point = ray.at(hit_record.t);
    Vec3 outward_normal = (hit_record.point - center_) / radius_;
    hit_record.set_face_normal(ray, outward_normal);
    hit_record.material_ptr = material_ptr_;

    return true;
}

bool Sphere::bounding_box(AABB& output_box) const {
    Point3 min = center_ - Point3(radius_, radius_, radius_);
    Point3 max = center_ + Point3(radius_, radius_, radius_);
    output_box = AABB(min, max);
//    output_box = AABB(
//            center_ - Point3(radius_, radius_, radius_),
//            center_ + Point3(radius_, radius_, radius_));
    return true;
}