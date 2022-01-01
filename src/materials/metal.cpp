//
// Created by jeang on 2021-12-31.
//

#include "materials/metal.h"

bool Metal::scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = reflect(unit_vector(ray_in.direction()), hit_record.normal);
    scattered = Ray(hit_record.point, reflected + fuzz_ * random_in_unit_sphere());
    attenuation = albedo_;
    return scattered.direction().dot(hit_record.normal) > 0;
};
