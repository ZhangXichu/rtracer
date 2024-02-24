#include <iostream>

#include "utils.hpp"

cv::Vec3d unit_vector(const cv::Vec3d v)
{
    double length = cv::norm(v);

    return v / length;
}

cv::Vec3d color(const Ray& r)
{
    cv::Vec3d unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction[1] + 1.0); // normalize y-axis range to [0, 1]

    cv::Vec3d v_e(1.0, 1.0, 1.0); // white
    cv::Vec3d v(0.6, 0.7, 1.0); // light blue

    return (1.0-t)*v_e + t*v; // linear interpolation
}
