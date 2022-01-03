#include "utils.h"
#include "hittable_list.h"
#include "Sphere.h"
#include "ray.h"
#include "camera.h"
#include "materials/metal.h"
#include "materials/lambertian.h"
#include "materials/dielectric.h"

#include <chrono>


// diffuse version 1 : spherical scattering
Color ray_color(const Ray& ray, const Hittable& world, int depth) {
    HitRecord hit_record;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0,0,0);

    if (world.hit(ray, 0.001, infinity, hit_record)){ // use a tolerance
        Ray scattered;
        Color attenuation;
        if (hit_record.material_ptr->scatter(ray, hit_record, attenuation, scattered)){
            return attenuation.cwiseProduct(ray_color(scattered, world, depth -1));
        }
        return Color(0,0,0);
    }
    Vec3 unit_direction = unit_vector(ray.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}


HittableList random_scene() {
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point3(4, 0.2, 0)).norm() > 0.9) {
                shared_ptr<Material> Sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
//                    auto albedo = Color::random() * Color::random();
                    Color albedo = random_vec(0.0, 1.0).cwiseProduct(random_vec(0.0, 1.0));
                    Sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, Sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
//                    auto albedo = Color::random(0.5, 1);
//                    auto fuzz = random_double(0, 0.5);
                    auto albedo = random_vec(0.5, 1.0);
                    auto fuzz = random_double() * 0.5;
                    Sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, Sphere_material));
                } else {
                    // glass
                    Sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, Sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

int main() {
    // Image
//    const auto aspect_ratio = 3.0 / 2.0;
//    const int image_width = 1200;
//    const int image_height = static_cast<int>(image_width / aspect_ratio);
//    const int samples_per_pixels = 500;
//    const int max_depth = 50;

    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 200;
//    const auto aspect_ratio = 16.0 / 9.0;
//    const int image_width = 256;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixels = 50;
    const int max_depth = 50;


    // World
    HittableList world = random_scene();


    // Camera
    Point3 lookfrom(13,2,3);
    Point3 lookat(0,0,0);
    Vec3 vup(0,1,0);
    auto dist_to_focus = 10;
    auto aperture = 0.1;

    Camera camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);



    // Render
    auto initial_time = std::chrono::steady_clock::now();

    fmt::print("P3\n{0} {1}\n255\n", image_width, image_height);

    for (int j = image_height-1; j >= 0; --j) {
        fmt::print(stderr, "\rScanlines remaining: {0}", j);
        for (int i = 0; i < image_width; ++i) {
            Color pixel_Color(0, 0, 0);
            for(int s = 0; s < samples_per_pixels; ++s){
                auto u = double(i + random_double()) / (image_width-1);
                auto v = double(j + random_double()) / (image_height-1);

                Ray ray = camera.get_ray(u,v);
                pixel_Color += ray_color(ray, world, max_depth);
            }
            write_color(pixel_Color, samples_per_pixels);
        }
    }
    auto final_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = final_time - initial_time;
    fmt::print(stderr, "\nDone.\n");
    fmt::print(stderr, "Elapsed time = {0} s\n", elapsed_seconds.count());
}
