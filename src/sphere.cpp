//
// Created by jeang on 2021-12-28.
//

#include "sphere.h"
#include <iostream>


bool Sphere::hit(const Ray &ray, double t_min, double t_max, HitRecord& hit_record) const
{
    Vec3 oc = ray.origin() - center_;
    double a = ray.direction().dot(ray.direction());
    double half_b = oc.dot(ray.direction()); // using half_b results in less computation for the same retults
    double c = oc.dot(oc) - radius_*radius_;
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) // does not touch
        return false;

    // Find the nearest root that lies in the acceptable range.
    double sqrt_discriminant = std::sqrt(discriminant);
    double root = (-half_b - sqrt_discriminant) / a ;// find closest root
    if (root < t_min || root > t_max){ // check if outside range
        root = (-half_b + sqrt_discriminant) / a ;
        if (root < t_min || root > t_max)
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
