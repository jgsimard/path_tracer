//
// Created by jeang on 2021-12-28.
//
#pragma once

#include <utility>

#include "vec.h"

class Ray {
public:
    Ray() = default;
    Ray(Point3  origin, Vec3  direction)
            : origin_(std::move(origin)), direction_(unit_vector(std::move(direction)))
    {}

    [[nodiscard]] Point3 origin() const  { return origin_; }
    [[nodiscard]] Vec3 direction() const { return direction_; }

    [[nodiscard]] Point3 at(float t) const {
        return origin_ + t * direction_;
    }

private:
    Point3 origin_;
    Vec3 direction_;
};
