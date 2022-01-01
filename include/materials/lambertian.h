//
// Created by jeang on 2021-12-31.
//

#pragma once

#include "material.h"
#include "hittable.h"

class Lambertian : public Material{ // diffuse material
public:
    Lambertian(const Color& albedo) : albedo_(albedo) {}

    bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override;
private:
    Color albedo_;
};