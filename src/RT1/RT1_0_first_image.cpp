#include "utils.h"

int main() {
    // Image
    const int image_width = 256;
    const int image_height = 256;

    // Render
    fmt::print("P3\n{0} {1}\n255\n", image_width, image_height);

    for (int j = image_height-1; j >= 0; --j) {
        fmt::print(stderr, "\rScanlines remaining: {0}", j);
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(double(i) / (image_width-1), double(j) / (image_height-1), 0.25);
            write_color(pixel_color);
        }
    }
    fmt::print(stderr, "\nDone.\n");
}