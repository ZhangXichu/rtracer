#ifndef UTILS_H
#define UTILS_H

#include <ray.hpp>
#include <opencv2/core/matx.hpp>
#include <datatypes.hpp>
#include <hittable.hpp>
#include <hittable_list.hpp>
#include <constants.hpp>
#include <cstdlib>

cv::Vec3d unit_vector(const cv::Vec3d v);
cv::Vec3d reflect(const cv::Vec3d& v, const cv::Vec3d& n);
bool near_zero(const cv::Vec3d v);
cv::Vec3d random_in_unit_sphere();
cv::Vec3d random_unit_vector();
cv::Vec3d random_on_hemisphere(const cv::Vec3d& normal);
double hit_sphere(const cv::Vec3d& center, double radius, const Ray& ray);
cv::Vec3d random_vector();
cv::Vec3d random_vector(double min, double max);
inline double degrees_to_radians(double degrees) {
    return degrees * R_PI / 180.0;
}
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}
inline double random_double(double min, double max) {
    return min + (max - min)*random_double();
}


#endif