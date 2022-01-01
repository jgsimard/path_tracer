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

class Hittable_list : public Hittable{
public:
    Hittable_list() {};
    Hittable_list(shared_ptr<Hittable> hittable){ add(hittable);}

    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const override;


    void clear(){hittables.clear();};
    void add(shared_ptr<Hittable> hittable){hittables.push_back(hittable);};


    vector<shared_ptr<Hittable>> hittables;
};

