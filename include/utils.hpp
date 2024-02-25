#ifndef UTILS_H
#define UTILS_H

#include <ray.hpp>
#include <opencv2/core/matx.hpp>

using Color = cv::Vec3d;

Color ray_color(const Ray& r);
cv::Vec3d unit_vector(const cv::Vec3d v);
double hit_sphere(const cv::Vec3d& center, double radius, const Ray& ray);


#endif