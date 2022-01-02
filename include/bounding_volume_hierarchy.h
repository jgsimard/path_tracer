//
// Created by jeang on 2022-01-01.
//

#pragma once

#include "utils.h"
#include "hittable.h"
#include "hittable_list.h"



class BoundingVolumeHierarchyNode : public Hittable {
public:
    BoundingVolumeHierarchyNode() = default;

    BoundingVolumeHierarchyNode(const HittableList& list, double time0, double time1)
            : BoundingVolumeHierarchyNode(list.hittables_, 0, list.hittables_.size(), time0, time1) {}

    BoundingVolumeHierarchyNode(
            const std::vector<shared_ptr<Hittable>>& src_objects,
            size_t start, size_t end, double time0, double time1);

    bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;

    bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    shared_ptr<Hittable> left_;
    shared_ptr<Hittable> right_;
    AABB box_;
};

using BvhNode = BoundingVolumeHierarchyNode;