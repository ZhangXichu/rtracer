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


Color ray_color(const Ray& ray, const Hittable& world) 
{
    HitRecord record;
    if (world.hit(ray, Interval(0, R_INFINITY), record)) {
        return 0.5 * (record.normal + Color(1, 1, 1));
    }
    cv::Vec3d unit_direction = unit_vector(ray.direction());
    auto a = 0.5 * (unit_direction[1] + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}