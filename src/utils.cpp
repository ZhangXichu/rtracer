#include <iostream>

#include "utils.hpp"

cv::Vec3d unit_vector(const cv::Vec3d v)
{
    double length = cv::norm(v);

    return v / length;
}

// checks if a ray hits the sphere
double hit_sphere(const cv::Vec3d& center, double radius, const Ray& ray)
{
    cv::Vec3d v_oc = ray.origin() - center;
    
    double a = ray.direction().dot(ray.direction());
    double half_b = v_oc.dot(ray.direction());
    double c = v_oc.dot(v_oc) - radius * radius;
    double discreminant = half_b * half_b - a*c;

    if (discreminant < 0) {
        return -1.0;
    } else {
        // std::cout << "(-b - sqrt(discreminant)) / (2.0*a) = " << (-b - sqrt(discreminant)) / (2.0*a) << std::endl;
        return (-half_b - sqrt(discreminant)) / a;
    }
}
