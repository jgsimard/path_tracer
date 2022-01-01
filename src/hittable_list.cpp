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
    for (const auto& hittable : hittables){
        if (hittable->hit(ray, t_min, closest_so_far, temp_hit_record))
        {
            hit_anything = true;
            closest_so_far = temp_hit_record.t;
            hit_record = temp_hit_record;
        }
    }
    return hit_anything;
}

