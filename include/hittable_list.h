//
// Created by jeang on 2021-12-28.
//

#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

using std::shared_ptr;
using std::make_shared;
using std::vector;

class HittableList : public Hittable{
public:
    HittableList() = default;
    HittableList(shared_ptr<Hittable> hittable){ add(hittable);}

    bool hit(const Ray& ray, float t_min, float t_max, HitRecord& hit_record) const override;
    bool bounding_box(AABB& output_box) const override;


    void clear(){hittables_.clear();};
    void add(shared_ptr<Hittable> hittable){hittables_.push_back(hittable);};


    vector<shared_ptr<Hittable>> hittables_;
};

