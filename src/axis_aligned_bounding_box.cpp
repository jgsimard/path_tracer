//
// Created by jeang on 2022-01-01.
//

#include "axis_aligned_bounding_box.h"


bool AxisAlignedBoundingBox::hit(const Ray& r, double t_min, double t_max) const {
    for (int a = 0; a < 3; a++) {
        auto t0 = fmin((minimum_[a] - r.origin()[a]) / r.direction()[a],
                       (maximum_[a] - r.origin()[a]) / r.direction()[a]);
        auto t1 = fmax((minimum_[a] - r.origin()[a]) / r.direction()[a],
                       (maximum_[a] - r.origin()[a]) / r.direction()[a]);
        t_min = fmax(t0, t_min);
        t_max = fmin(t1, t_max);
        if (t_max <= t_min)
            return false;
    }
    return true;
}

//// optimized version : TODO test the two hit functions
//bool AxisAlignedBoundingBox::hit(const Ray& ray, double t_min, double t_max) const {
//    for (int a = 0; a < 3; a++) {
//        auto invD = 1.0f / ray.direction()[a];
//        auto t0 = (minimum()[a] - ray.origin()[a]) * invD;
//        auto t1 = (maximum()[a] - ray.origin()[a]) * invD;
//        if (invD < 0.0f)
//            std::swap(t0, t1);
//        t_min = t0 > t_min ? t0 : t_min;
//        t_max = t1 < t_max ? t1 : t_max;
//        if (t_max <= t_min)
//            return false;
//    }
//    return true;
//}

AABB surrounding_box(const AABB& box0, const AABB& box1) {
    // TODO optimize this : will be easy using Eigen::Array
    Point3 small = box0.minimum().cwiseMin(box1.minimum());
    Point3 big = box0.maximum().cwiseMax(box1.maximum());

//    Point3 small(fmin(box0.minimum().x(), box1.minimum().x()),
//                 fmin(box0.minimum().y(), box1.minimum().y()),
//                 fmin(box0.minimum().z(), box1.minimum().z()));
//
//
//    Point3 big(fmax(box0.maximum().x(), box1.maximum().x()),
//               fmax(box0.maximum().y(), box1.maximum().y()),
//               fmax(box0.maximum().z(), box1.maximum().z()));

    return AABB(small,big);
}