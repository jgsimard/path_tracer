//
// Created by jeang on 2021-12-31.
//

#include "materials/dielectric.h"
#include "vec.h"

bool Dielectric::scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const
{
    static  Color white(1.0f, 1.0f, 1.0f);
    attenuation = white;
//    attenuation = Color(1.0f, 1.0f, 1.0f);
    float ratio_index_of_refraction = hit_record.front_face ? 1.0f / index_of_refraction_ : index_of_refraction_; // assume the outside is air, TODO : change this!!!

    Vec3 unit_direction = ray_in.direction(); // ray_in.direction() is a unit vector by constuction

    float cos_theta = std::min(dot(-unit_direction, hit_record.normal), 1.0f);
    float sin_theta = sqrt(1.0f - cos_theta * cos_theta);
//    float sin_theta = sqrt1(1.0f - cos_theta * cos_theta);

    bool total_internal_reflection = ratio_index_of_refraction * sin_theta >= 1.0f;

    Vec3 out_direction;

    if (total_internal_reflection || reflectance(cos_theta, ratio_index_of_refraction) > random_double()){
        out_direction = reflect(unit_direction, hit_record.normal);
    }else{
        out_direction = refract(unit_direction, hit_record.normal, ratio_index_of_refraction);
    }

    scattered = Ray(hit_record.point, out_direction);
    return true;
}

float Dielectric::reflectance(float cos_theta, float ratio_index_of_refraction)
{   // Use Schlick's approximation for reflectance. // TODO : must learn in details what this is!!!
    float  r0 = (1.0f - ratio_index_of_refraction) / (1.0f + ratio_index_of_refraction);
    r0 = r0 * r0;
    return r0 + (1.0f-r0) * pow((1.0f - cos_theta),5.0f);
}