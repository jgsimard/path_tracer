//
// Created by jeang on 2021-12-31.
//

#pragma once

#include "utils.h"
#include "ray.h"
#include "forward_declarations.h"

//struct HitRecord; // declare it to not have circular dependency

class Material{
public:
    virtual bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const = 0;
};

