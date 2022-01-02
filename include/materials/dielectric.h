//
// Created by jeang on 2021-12-31.
//

#pragma once

#include "material.h"
#include "hittable.h"

class Dielectric : public Material{ // diffuse material
public:
    Dielectric(float index_of_refraction) : index_of_refraction_(index_of_refraction) {}

    virtual bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override;

    float index_of_refraction_;

private:
    static float reflectance(float cos_theta, float ratio_index_of_refraction);
};