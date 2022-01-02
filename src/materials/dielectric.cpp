//
// Created by jeang on 2021-12-31.
//

#include "materials/dielectric.h"
#include "vec.h"

bool Dielectric::scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double ratio_index_of_refraction = hit_record.front_face ? 1.0 / index_of_refraction_ : index_of_refraction_; // assume the outside is air, TODO : change this!!!

    Vec3 unit_direction = ray_in.direction(); // ray_in.direction() is a unit vector by constuction

    double cos_theta = std::min(dot(-unit_direction, hit_record.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool total_internal_reflection = ratio_index_of_refraction * sin_theta >= 1.0;

    Vec3 out_direction;

    if (total_internal_reflection || reflectance(cos_theta, ratio_index_of_refraction) > random_double()){
        out_direction = reflect(unit_direction, hit_record.normal);
    }else{
        out_direction = refract(unit_direction, hit_record.normal, ratio_index_of_refraction);
    }

    scattered = Ray(hit_record.point, out_direction);
    return true;
}

double Dielectric::reflectance(double cos_theta, double ratio_index_of_refraction)
{   // Use Schlick's approximation for reflectance. // TODO : must learn in details what this is!!!
    double  r0 = (1 - ratio_index_of_refraction) / (1 + ratio_index_of_refraction);
    r0 = r0 * r0;
    return r0 + (1-r0) * pow((1 - cos_theta),5);
}