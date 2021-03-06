#include "utils.h"
#include "ray.h"
#include <fmt/core.h>

static constexpr Color black(0.0f, 0.0f, 0.0f);
static constexpr Color white(1.0f, 1.0f, 1.0f);
static constexpr Color blue(0.5f, 0.7f, 1.0f);

Color ray_color(const Ray& ray) {
    float t = 0.5 * (ray.direction()[1] + 1.0f);
    return (1.0f-t) * white+ t * blue;
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

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
            auto direction = lower_left_corner + u*horizontal + v*vertical - origin;

            Ray ray(origin, direction);
            Color pixel_color = ray_color(ray);
            write_color(pixel_color);
        }
    }
    fmt::print(stderr, "\nDone.\n");
}
