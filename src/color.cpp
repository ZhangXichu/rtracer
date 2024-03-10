#include <color.hpp>
#include <interval.hpp>
#include <iostream>

Color write_color(Color pixel_color, int sample_per_pixel)
{
    auto r = pixel_color[0];
    auto g = pixel_color[1];
    auto b = pixel_color[2];

    auto scale = 1.0 / sample_per_pixel;
    r = r * scale; 
    g = g * scale;
    b = b * scale;

    // apply the linear to gamma transform
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const Interval intensity(0.000, 0.999);

    int ir = static_cast<int>(255.99 * intensity.clamp(r));
    int ig = static_cast<int>(255.99 * intensity.clamp(g));
    int ib = static_cast<int>(255.99 * intensity.clamp(b));

    return cv::Vec3b(ib, ig, ir);
}