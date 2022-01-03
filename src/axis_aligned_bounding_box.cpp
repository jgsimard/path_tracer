//
// Created by jeang on 2022-01-01.
//

#include "axis_aligned_bounding_box.h"


//bool AxisAlignedBoundingBox::hit(const Ray& r, float t_min, float t_max) const {
//    for (int a = 0; a < 3; a++) {
//        auto t0 = fmin((minimum_[a] - r.origin()[a]) / r.direction()[a],
//                       (maximum_[a] - r.origin()[a]) / r.direction()[a]);
//        auto t1 = fmax((minimum_[a] - r.origin()[a]) / r.direction()[a],
//                       (maximum_[a] - r.origin()[a]) / r.direction()[a]);
//        t_min = fmax(t0, t_min);
//        t_max = fmin(t1, t_max);
//        if (t_max <= t_min)
//            return false;
//    }
//    return true;
//}

// optimized version : lol 2X speedup
bool AxisAlignedBoundingBox::hit(const Ray& ray, float t_min, float t_max) const {
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / ray.direction()[a];
        auto t0 = (minimum()[a] - ray.origin()[a]) * invD;
        auto t1 = (maximum()[a] - ray.origin()[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}

AABB surrounding_box(const AABB& box0, const AABB& box1)
{
    Point3 small = min(box0.minimum(), box1.minimum());
    Point3 big = max(box0.maximum(), box1.maximum());
    return AABB(small,big);
}