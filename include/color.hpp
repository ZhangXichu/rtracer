#ifndef COLOR_H
#define COLOR_H

#include <datatypes.hpp>

Color write_color(Color pixel_color, int sample_per_pixel);
inline double linear_to_gamma(double linear_component)
{
    return sqrt(linear_component);
}

#endif