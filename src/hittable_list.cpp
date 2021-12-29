//
// Created by jeang on 2021-12-28.
//

#include "hittable_list.h"

bool Hittable_list::hit(const Ray &ray, double t_min, double t_max, Hit_record &hit_record) const
{
    Hit_record temp_hit_record;
    bool hit_anything = false;
    bool closest_so_far = t_max;
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
