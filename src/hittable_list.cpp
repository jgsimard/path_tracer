//
// Created by jeang on 2021-12-28.
//

#include "hittable_list.h"
#include <fmt/core.h>

bool HittableList::hit(const Ray &ray, double t_min, double t_max, HitRecord &hit_record) const
{
    HitRecord temp_hit_record;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (const auto& hittable : hittables_){
        if (hittable->hit(ray, t_min, closest_so_far, temp_hit_record))
        {
            hit_anything = true;
            closest_so_far = temp_hit_record.t;
            hit_record = temp_hit_record;
        }
    }
    return hit_anything;
}

bool HittableList::bounding_box(double time0, double time1, AABB& output_box) const {
    if (hittables_.empty()) return false;

    AABB temp_box;
    bool first_box = true;

    for (const auto& hittable : hittables_) {
        if (!hittable->bounding_box(time0, time1, temp_box)) return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}

