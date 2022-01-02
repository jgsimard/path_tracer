//
// Created by jeang on 2022-01-01.
//

#include "bounding_volume_hierarchy.h"


bool BoundingVolumeHierarchyNode::bounding_box(double time0, double time1, AABB& output_box) const {
    output_box = box_;
    return true;
}

bool BoundingVolumeHierarchyNode::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
//    fmt::print(stderr, "BoundingVolumeHierarchyNode::hit.\n");
    if (!box_.hit(ray, t_min, t_max))
        return false;

    bool hit_left = left_->hit(ray, t_min, t_max, rec);
    bool hit_right = right_->hit(ray, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

inline bool box_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->bounding_box(0,0, box_a) || !b->bounding_box(0,0, box_b))
        fmt::print(stderr, "No bounding box in bvh_node constructor.\n");
//        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.minimum()[axis] < box_b.minimum()[axis];
}


bool box_x_compare (const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return box_compare(a, b, 0);
}

bool box_y_compare (const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return box_compare(a, b, 1);
}

bool box_z_compare (const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
    return box_compare(a, b, 2);
}

BoundingVolumeHierarchyNode::BoundingVolumeHierarchyNode(
        const std::vector<shared_ptr<Hittable>>& src_objects,
        size_t start, size_t end, double time0, double time1
) {
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = random_int(0,2);
    auto comparator = (axis == 0) ? box_x_compare
                                  : (axis == 1) ? box_y_compare
                                                : box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left_ = right_ = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left_ = objects[start];
            right_ = objects[start+1];
        } else {
            left_ = objects[start+1];
            right_ = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        left_ = make_shared<BoundingVolumeHierarchyNode>(objects, start, mid, time0, time1);
        right_ = make_shared<BoundingVolumeHierarchyNode>(objects, mid, end, time0, time1);
    }

    AABB box_left, box_right;

    if (  !left_->bounding_box (time0, time1, box_left)
          || !right_->bounding_box(time0, time1, box_right)
            )
        fmt::print(stderr, "No bounding box in bvh_node constructor.\n");
//        std::cerr << "No bounding box in bvh_node constructor.\n";

    box_ = surrounding_box(box_left, box_right);
}

