//
// Created by jeang on 2021-12-28.
//
#pragma once

#include <utility>

#include "hittable.h"

class Sphere : public Hittable{
public:
    Sphere() {};
    Sphere(Point3 center, double radius) : center_(std::move(center)), radius_(radius) {}; // so that the past stuff can still run
    Sphere(Point3 center, double radius, shared_ptr<Material> material) : center_(std::move(center)), radius_(radius), material_ptr_(std::move(material)) {};

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const override;

    Point3 center_;
    double radius_;
    shared_ptr<Material> material_ptr_;
};
