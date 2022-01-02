//
// Created by jeang on 2021-12-31.
//

#pragma once

#include "material.h"
#include "hittable.h"


class Metal : public Material{
public:
    Metal(const Color& albedo, float fuzz) : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1.0) {}

    virtual bool scatter(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override;

    Color albedo_;
    float fuzz_;
};