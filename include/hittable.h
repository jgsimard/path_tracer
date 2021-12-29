//
// Created by jeang on 2021-12-28.
//

#ifndef GRAPHICS_HITTABLE_H
#define GRAPHICS_HITTABLE_H

#include "utils.h"
#include "ray.h"

struct Hit_record{
    Point3 point;
    Vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray& ray, const Vec3& outward_normal){
        front_face = ray.direction().dot(outward_normal) < 0;
        normal = front_face ? outward_normal : - outward_normal;
    }
};

class Hittable{
public:
    virtual bool hit(const Ray& ray, double t_min, double t_max, Hit_record& hit_record) const = 0;
};
#endif //GRAPHICS_HITTABLE_H
