//
// Created by jeang on 2021-12-28.
//

#include "sphere.h"

bool Sphere::hit(const Ray &ray, double t_min, double t_max, HitRecord& hit_record) const
{
    Vec3 oc = ray.origin() - center_;
//    double a = dot(ray.direction(), ray.direction()); // =1 by definition
    double half_b = dot(oc, ray.direction()); // using half_b results in less computation for the same retults
//    double c = dot(oc, oc) - radius_*radius_;
    double c = dot(oc, oc) - radius_square_;
//    double discriminant = half_b * half_b - a * c;
    double discriminant = half_b * half_b - c; // a=1 by construction
    if (discriminant < 0) // does not touch
        return false;

    // Find the nearest root that lies in the acceptable range.
    double sqrt_discriminant = std::sqrt(discriminant);
//    double root = (-half_b - sqrt_discriminant) / a ;// find closest root
    double root = (-half_b - sqrt_discriminant)  ;// find closest root
    if (root < t_min || root > t_max){ // check if outside range
//        root = (-half_b + sqrt_discriminant) / a ;
        root = (-half_b + sqrt_discriminant) ;
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
