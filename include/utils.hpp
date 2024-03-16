#ifndef UTILS_H
#define UTILS_H

#include <ray.hpp>
#include <opencv2/core/matx.hpp>
#include <datatypes.hpp>
#include <hittable.hpp>
#include <hittable_list.hpp>
#include <constants.hpp>
#include <cstdlib>
#include <iostream>
#include <random>

cv::Vec3d unit_vector(const cv::Vec3d v);
cv::Vec3d pointwise(const cv::Vec3d v, const cv::Vec3d u);
cv::Vec3d reflect(const cv::Vec3d& v, const cv::Vec3d& n);
inline cv::Vec3d refract(const cv::Vec3d& uv, const cv::Vec3d& n, double etai_over_etat)
{
    auto cos_theta = fmin((-uv).dot(n), 1.0);

    // std::cout << "cos_theta : " << cos_theta << std::endl;

    cv::Vec3d r_out_perp = etai_over_etat * (uv + cos_theta * n); 
    cv::Vec3d r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.dot(r_out_perp))) * n;

    return r_out_perp + r_out_parallel;
}
bool near_zero(const cv::Vec3d v);
cv::Vec3d random_in_unit_sphere();
cv::Vec3d random_unit_vector();
cv::Vec3d random_on_hemisphere(const cv::Vec3d& normal);
double hit_sphere(const cv::Vec3d& center, double radius, const Ray& ray);
cv::Vec3d random_vector();
inline double degrees_to_radians(double degrees) {
    return degrees * R_PI / 180.0;
}
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}


#endif