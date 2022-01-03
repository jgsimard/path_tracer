//
// Created by jeang on 2021-12-28.
//
#pragma once

#include "utils.h"
#include "ray.h"
#include "axis_aligned_bounding_box.h"

class Material;

struct HitRecord{
    Point3 point;
    Vec3 normal;
    shared_ptr<Material> material_ptr;
    float t;
    bool front_face;

    inline void set_face_normal(const Ray& ray, const Vec3& outward_normal){
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : - outward_normal;
    }
};

class Hittable{
public:
    virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& hit_record) const = 0;
    virtual bool bounding_box(AABB& output_box) const = 0;
};