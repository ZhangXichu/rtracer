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

Color ray_color(const Ray& ray)
{
    cv::Vec3d center_s(0.0, 0.0, -1.0);

    auto d = hit_sphere(center_s, 0.5, ray);
    
    if (d > 0) {
        // std::cout << "d = " << d << std::endl;

        cv::Vec3d norm = unit_vector(ray.at(d) - center_s);
        return 0.5 * Color(norm[0]+1, norm[1]+1, norm[2]+1);
    }

    cv::Vec3d unit_direction = unit_vector(ray.direction());
    double t = 0.5 * (unit_direction[1] + 1.0); // normalize y-axis range to [0, 1]

    Color v_e(1.0, 1.0, 1.0); // white
    Color v(0.075, 0.576, 0.929); // light blue

    return (1.0-t)*v_e + t*v; // linear interpolation
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