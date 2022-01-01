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

class Dielectric : public Material{ // diffuse material
public:
    Dielectric(double index_of_refraction) : index_of_refraction_(index_of_refraction) {}

    virtual bool scatter(const Ray& ray_in, const Hit_record& hit_record, Color& attenuation, Ray& scattered) const override
    {
        attenuation = Color(1.0, 1.0, 1.0);
        double ratio_index_of_refraction = hit_record.front_face ? 1.0 / index_of_refraction_ : index_of_refraction_; // assume the outside is air, TODO : change this!!!

        Vec3 unit_direction = unit_vector(ray_in.direction());

        double cos_theta = std::min(-unit_direction.dot(hit_record.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool total_internal_reflection = ratio_index_of_refraction * sin_theta >= 1.0;

        Vec3 out_direction;

        if (total_internal_reflection || reflectance(cos_theta, ratio_index_of_refraction) > random_double()){
            out_direction = reflect(unit_direction, hit_record.normal);
        }else{
            out_direction = refract(unit_direction, hit_record.normal, ratio_index_of_refraction);
        }

        scattered = Ray(hit_record.point, out_direction);
        return true;
    };

    double index_of_refraction_;

private:
    static double reflectance(double cos_theta, double ratio_index_of_refraction)
    {   // Use Schlick's approximation for reflectance. // TODO : must learn in details what this is!!!
        double  r0 = (1 - ratio_index_of_refraction) / (1 + ratio_index_of_refraction);
        r0 = r0 * r0;
        return r0 + (1-r0) * pow((1 - cos_theta),5);
    }
};
