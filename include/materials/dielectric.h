//
// Created by jeang on 2021-12-31.
//

#pragma once

#include "material.h"
#include "hittable.h"

class Dielectric : public Material{ // diffuse material
public:
    Dielectric(double index_of_refraction) : index_of_refraction_(index_of_refraction) {}

    virtual bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override;

    double index_of_refraction_;

private:
    static double reflectance(double cos_theta, double ratio_index_of_refraction);
};