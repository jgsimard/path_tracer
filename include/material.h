//
// Created by jeang on 2021-12-31.
//

#pragma once

#include "utils.h"
#include "ray.h"

struct Hit_record; // declare it to not have circular depedancy

class Material{
public:
    virtual bool scatter(const Ray& ray_in, const Hit_record& hit_record, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material{ // diffuse material
public:
    Lambertian(const Color& albedo) : albedo_(albedo) {}

    virtual bool scatter(const Ray& ray_in, const Hit_record& hit_record, Color& attenuation, Ray& scattered) const override
    {
        Vec3 scatter_direction = hit_record.point + hit_record.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (near_zero(scatter_direction))
            scatter_direction = hit_record.normal;


        scattered = Ray(hit_record. point, scatter_direction);
        attenuation = albedo_;
        return true;
    };

    Color albedo_;
};

class Metal : public Material{ // diffuse material
public:
    Metal(const Color& albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1.0) {}

    virtual bool scatter(const Ray& ray_in, const Hit_record& hit_record, Color& attenuation, Ray& scattered) const override
    {
        Vec3 reflected = reflect(unit_vector(ray_in.direction()), hit_record.normal);
        scattered = Ray(hit_record.point, reflected + fuzz_ * random_in_unit_sphere());
        attenuation = albedo_;
        return scattered.direction().dot(hit_record.normal) > 0;
    };

    Color albedo_;
    double fuzz_;
};