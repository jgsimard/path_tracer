#include "utils.h"
#include "hittable_list.h"
#include "sphere.h"
#include "ray.h"
#include "camera.h"
#include "materials/metal.h"
#include "materials/lambertian.h"
#include "materials/dielectric.h"
#include "bounding_volume_hierarchy.h"

#include <chrono>

static constexpr Color black(0.0f, 0.0f, 0.0f);
static constexpr Color white(1.0f, 1.0f, 1.0f);
static constexpr Color blue(0.5f, 0.7f, 1.0f);

Color ray_color(const Ray& ray, const Hittable& world, int depth) {
    HitRecord hit_record;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0.0f)
        return black;

    if (world.hit(ray, 0.001, infinity, hit_record)){ // use a tolerance
        Ray scattered;
        Color attenuation;
        if (hit_record.material_ptr->scatter(ray, hit_record, attenuation, scattered)){
            return attenuation * ray_color(scattered, world, depth -1);
        }
        return black;
    }

    float t = 0.5 * (ray.direction()[1] + 1.0f);
    return (1.0f-t) * white+ t * blue;
}


HittableList random_scene() {
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.5f, 0.5f, 0.5f));
    world.add(make_shared<Sphere>(Point3(0.0f,-1000.0f,0.0f), 1000.0f, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9f * random_double(), 0.2f, b + 0.9f * random_double());

            if (length(center - Point3(4.0f, 0.2f, 0.0f)) > 0.9f) {
                shared_ptr<Material> Sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    Color albedo = random_vec01() * random_vec01();
                    Sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2f, Sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_vec(0.5f, 1.0f);
                    auto fuzz = random_double() * 0.5f;
                    Sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2f, Sphere_material));
                } else {
                    // glass
                    Sphere_material = make_shared<Dielectric>(1.5f);
                    world.add(make_shared<Sphere>(center, 0.2f, Sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5f);
    world.add(make_shared<Sphere>(Point3(0.0f, 1.0f, 0.0f), 1.0f, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    world.add(make_shared<Sphere>(Point3(-4.0f, 1.0f, 0.0f), 1.0f, material2));

    auto material3 = make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    world.add(make_shared<Sphere>(Point3(4.0f, 1.0f, 0.0f), 1.0f, material3));

    return world;
}



int main() {
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixels = 500;
    const int max_depth = 50;


    // World
    HittableList world = random_scene();

    fmt::print(stderr, "Building BVH ...");
    auto bvh_start_time = std::chrono::steady_clock::now();

    world = HittableList(make_shared<BvhNode>(world, 0.0f, 1.0f));

    auto bvh_final_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> bvh_elapsed_seconds = bvh_final_time - bvh_start_time;
    fmt::print(stderr, "\rBuilding BVH ... Done. Took {0} s\n", bvh_elapsed_seconds.count());


    // Camera
    Point3 lookfrom(13.0f,2.0f,3.0f);
    Point3 lookat(0.0f,0.0f,0.0f);
    Vec3 vup(0.0f,1.0f,0.0f);
    auto dist_to_focus = 10.0f;
    auto aperture = 0.1f;

    Camera camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);



    // Render
    auto initial_time = std::chrono::steady_clock::now();

    fmt::print("P3\n{0} {1}\n255\n", image_width, image_height);

    for (int j = image_height-1; j >= 0; --j) {
        fmt::print(stderr, "\rScanlines remaining: {0}", j);
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for(int s = 0; s < samples_per_pixels; ++s){
                auto u = float(i + random_double()) / (image_width-1);
                auto v = float(j + random_double()) / (image_height-1);

                Ray ray = camera.get_ray(u, v);
                pixel_color = pixel_color + ray_color(ray, world, max_depth);
            }
            write_color(pixel_color, samples_per_pixels);
        }
    }
    auto final_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = final_time - initial_time;
    fmt::print(stderr, "\nDone.\n");
    fmt::print(stderr, "Elapsed time = {0} s\n", elapsed_seconds.count());
}
