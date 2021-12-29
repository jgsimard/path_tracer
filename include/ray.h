//
// Created by jeang on 2021-12-28.
//

#ifndef GRAPHICS_RAY_H
#define GRAPHICS_RAY_H

#include "utils.h"

class Ray {
public:
    Ray() {}
    Ray(const Point3& origin, const Vec3& direction)
            : orig(origin), dir(direction)
    {}

    Point3 origin() const  { return orig; }
    Vec3 direction() const { return dir; }

    Point3 at(double t) const {
        return orig + t * dir;
    }

public:
    Point3 orig;
    Vec3 dir;
};


#endif //GRAPHICS_RAY_H
