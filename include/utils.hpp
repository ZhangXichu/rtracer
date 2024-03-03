#ifndef UTILS_H
#define UTILS_H

#include <ray.hpp>
#include <opencv2/core/matx.hpp>
#include <datatypes.hpp>
#include <hittable.hpp>
#include <hittable_list.hpp>
#include <constants.hpp>

Color ray_color(const Ray& r);
Color ray_color(const Ray& ray, const Hittable& world);
cv::Vec3d unit_vector(const cv::Vec3d v);
double hit_sphere(const cv::Vec3d& center, double radius, const Ray& ray);
inline double degrees_to_radians(double degrees) {
    return degrees * R_PI / 180.0;
}


#endif