//
// Created by jeang on 2021-12-31.
//

#pragma once

#include "material.h"

class Lambertian : public Material{ // diffuse material
public:
    Lambertian(const Color& albedo) : albedo_(albedo) {}

//    bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override
//    {
//        Vec3 scatter_direction = hit_record.point + hit_record.normal + random_unit_vector();
//
//        // Catch degenerate scatter direction
//        if (near_zero(scatter_direction))
//            scatter_direction = hit_record.normal;
//
//
//        scattered = Ray(hit_record. point, scatter_direction);
//        attenuation = albedo_;
//        return true;
//    }

    bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override;
private:
    Color albedo_;
};