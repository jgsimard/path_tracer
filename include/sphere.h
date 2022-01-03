//
// Created by jeang on 2021-12-28.
//
#pragma once

#include "hittable.h"
#include "vec.h"

class Sphere : public Hittable{
public:
    Sphere() = default;
    Sphere(Point3 center, float radius) : center_(std::move(center)), radius_(radius) , radius_square_(radius*radius) {}; // so that the past stuff can still run
    Sphere(Point3 center, float radius, shared_ptr<Material> material) : center_(std::move(center)), radius_(radius), radius_square_(radius*radius), material_ptr_(std::move(material)) {};

    virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& hit_record) const override;
    virtual bool bounding_box(AABB& output_box) const override;

private:
    Point3 center_;
    float radius_;
    float radius_square_;
    shared_ptr<Material> material_ptr_;
};
