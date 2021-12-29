// C++
#include <iostream>

// ME
#include "utils.h"
#include "hittable_list.h"
#include "sphere.h"
#include "ray.h"
#include "camera.h"


Color ray_color(const Ray& ray, const Hittable& world) {
    Hit_record hit_record;
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
    const int samples_per_pixels = 100;

    // World
    Hittable_list world;
    world.add(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(Point3(0,-100.5, -1), 100));

    // Camera
    Camera camera;

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for(int s = 0; s < samples_per_pixels; ++s){
                auto u = double(i + random_double()) / (image_width-1);
                auto v = double(j + random_double()) / (image_height-1);

                Ray ray = camera.get_ray(u,v);
                pixel_color += ray_color(ray, world);
            }
            write_color(pixel_color, samples_per_pixels);
        }
    }
    std::cerr << "\nDone.\n";
}
