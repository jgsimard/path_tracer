//
// Created by jeang on 2022-01-01.
//

#pragma once

#include "vec.h"
#include "ray.h"

class AxisAlignedBoundingBox {
public:
    AxisAlignedBoundingBox() = default;
    AxisAlignedBoundingBox(Point3& minimum, Point3& maximum) : minimum_(minimum), maximum_(maximum) {};


    Point3 minimum() const {return minimum_; }
    Point3 maximum() const {return maximum_; }

    bool hit(const Ray& ray, float t_min, float t_max) const;



private:
    Point3 minimum_;
    Point3 maximum_;

};

using AABB = AxisAlignedBoundingBox;

AABB surrounding_box(const AABB& box0, const AABB& box1);
