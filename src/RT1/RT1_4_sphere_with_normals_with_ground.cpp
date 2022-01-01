#include "utils.h"
#include "hittable_list.h"
#include "sphere.h"
#include "ray.h"


Color ray_color(const Ray& ray, const Hittable& world) {
    HitRecord hit_record;
    if (world.hit(ray, 0, infinity, hit_record)){
        return 0.5 * (hit_record.normal + Color(1,1,1));
    }
    Vec3 unit_direction = unit_vector(ray.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    HittableList world;
    world.add(make_shared<Sphere>(Point3(0,-100.5, -1), 100));
    world.add(make_shared<Sphere>(Point3(0,0,-1), 0.5));

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    Point3 origin = Point3(0, 0, 0);
    Vec3 horizontal = Vec3(viewport_width, 0, 0);
    Vec3 vertical = Vec3(0, viewport_height, 0);
    Point3 lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

    // Render
    fmt::print("P3\n{0} {1}\n255\n", image_width, image_height);

    for (int j = image_height-1; j >= 0; --j) {
        fmt::print(stderr, "\rScanlines remaining: {0}", j);
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            auto direction = lower_left_corner + u * horizontal + v * vertical - origin;

            Ray ray(origin, direction);
            Color pixel_color = ray_color(ray, world);
            write_color(pixel_color);
        }
    }
    fmt::print(stderr, "\nDone.\n");
}
