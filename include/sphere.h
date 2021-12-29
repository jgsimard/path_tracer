//
// Created by jeang on 2021-12-28.
//

#ifndef GRAPHICS_SPHERE_H
#define GRAPHICS_SPHERE_H

#include "hittable.h"

class Sphere : public Hittable{
public:
    Sphere() {};
    Sphere(Point3 center, double radius) : center_(center), radius_(radius) {};

    virtual bool hit(const Ray& ray, double t_min, double t_max, Hit_record& hit_record) const override;

    Point3 center_;
    double radius_;
};

#endif //GRAPHICS_SPHERE_H
