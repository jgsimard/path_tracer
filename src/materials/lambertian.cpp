//
// Created by jeang on 2021-12-31.
//

#include "materials/lambertian.h"

bool Lambertian::scatter(const Ray& /*ray_in*/, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const
{
   Vec3 scatter_direction = hit_record.normal + random_unit_vector();
    // Vec3 scatter_direction = hit_record.point  + random_unit_vector();
//    Vec3 scatter_direction = hit_record.point  + random_in_hemisphere(hit_record.normal);

    // Catch degenerate scatter direction
    if (near_zero(scatter_direction))
        scatter_direction = hit_record.normal;

    scattered = Ray(hit_record.point, scatter_direction);
    attenuation = albedo_;
    return true;
}