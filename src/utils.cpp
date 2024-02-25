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
    double b = 2.0 * v_oc.dot(ray.direction());
    double c = v_oc.dot(v_oc) - radius * radius;
    double discreminant = b*b - 4*a*c;

    // std::cout << "a = " << a << ", b = " <<  b << ", c = " << c << ", discreminant = " << discreminant << std::endl;

    if (discreminant < 0) {
        return -1.0;
    } else {
        // std::cout << "(-b - sqrt(discreminant)) / (2.0*a) = " << (-b - sqrt(discreminant)) / (2.0*a) << std::endl;
        return (-b - sqrt(discreminant)) / (2.0*a);
    }
}

Color ray_color(const Ray& ray)
{
    cv::Vec3d center_s(0.0, 0.0, -1.0);

    auto d = hit_sphere(center_s, 0.5, ray);

    // std::cout << "d = " << d << std::endl;
    
    if (d > 0) {
        std::cout << "d = " << d << std::endl;

        cv::Vec3d norm = unit_vector(ray.at(d) - center_s);
        return 0.5 * Color(norm[0]+1, norm[1]+1, norm[2]+1);
    }

    // if (hit_sphere(center_s, 0.5, ray))
    //     return Color(1, 0, 0); // color it red

    cv::Vec3d unit_direction = unit_vector(ray.direction());
    double t = 0.5 * (unit_direction[1] + 1.0); // normalize y-axis range to [0, 1]

    Color v_e(1.0, 1.0, 1.0); // white
    Color v(0.075, 0.576, 0.929); // light blue

    return (1.0-t)*v_e + t*v; // linear interpolation
}
