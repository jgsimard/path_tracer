#include "utils.h"
#include "hittable_list.h"
#include "sphere.h"
#include "ray.h"
#include "camera.h"

// diffuse version 1 : spherical scattering
Color ray_color(const Ray& ray, const Hittable& world, int depth) {
    Hit_record hit_record;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0,0,0);

    if (world.hit(ray, 0.001, infinity, hit_record)){ // use a tolerance
        Point3 target = hit_record.point + hit_record.normal + random_unit_vector();
        return 0.5 * ray_color(Ray(hit_record.point, target - hit_record.point), world, depth - 1);
    }
    Vec3 unit_direction = unit_vector(ray.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

//diffuse version 2 : hemispherical scattering
Color ray_color2(const Ray& ray, const Hittable& world, int depth) {
    Hit_record hit_record;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0,0,0);

    if (world.hit(ray, 0.001, infinity, hit_record)){ // use a tolerance
        Point3 target = hit_record.point + random_in_hemisphere(hit_record.point);
        return 0.5 * ray_color(Ray(hit_record.point, target - hit_record.point), world, depth - 1);
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
    const int samples_per_pixels = 100;
    const int max_depth = 50;

    // World
    Hittable_list world;
    world.add(make_shared<Sphere>(Point3(0,-1000.5, -1), 1000));
    world.add(make_shared<Sphere>(Point3(0,0,-1), 0.5));

    // Camera
    Camera camera;

    // Render
    fmt::print("P3\n{0} {1}\n255\n", image_width, image_height);

    for (int j = image_height-1; j >= 0; --j) {
        fmt::print(stderr, "\rScanlines remaining: {0}", j);
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for(int s = 0; s < samples_per_pixels; ++s){
                auto u = double(i + random_double()) / (image_width-1);
                auto v = double(j + random_double()) / (image_height-1);

                Ray ray = camera.get_ray(u,v);
                pixel_color += ray_color(ray, world, max_depth);
            }
            write_color(pixel_color, samples_per_pixels);
        }
    }
    fmt::print(stderr, "\nDone.\n");
}
