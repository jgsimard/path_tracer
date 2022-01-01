//
// Created by jeang on 2021-12-31.
//

#pragma once

#include "material.h"

struct HitRecord; // declare it to not have circular depedancy

class Metal : public Material{ // diffuse material
public:
    Metal(const Color& albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1.0) {}

    virtual bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override
    {
        Vec3 reflected = reflect(unit_vector(ray_in.direction()), hit_record.normal);
        scattered = Ray(hit_record.point, reflected + fuzz_ * random_in_unit_sphere());
        attenuation = albedo_;
        return scattered.direction().dot(hit_record.normal) > 0;
    };

    Color albedo_;
    double fuzz_;
};