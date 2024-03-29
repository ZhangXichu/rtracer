#include <iostream>

#include "utils.hpp"

cv::Vec3d unit_vector(const cv::Vec3d v)
{
    double length = cv::norm(v);

    return v / length;
}

cv::Vec3d pointwise(const cv::Vec3d v, const cv::Vec3d u)
{
    return cv::Vec3d(v[0]*u[0], v[1]*u[1], v[2]*u[2]);
}

cv::Vec3d reflect(const cv::Vec3d& v, const cv::Vec3d& n)
{
    return v - 2*v.dot(n)*n;
}


bool near_zero(const cv::Vec3d v) 
{
    // return true if the vector is close to zero in all dimensions
    auto s = 1e-8;
    return (fabs(v[0]) < s) && (fabs(v[1]) < s) && (fabs(v[2]) < s);
}

cv::Vec3d random_in_unit_sphere()
{
    while (true) {
        auto p = random_vector();
        if (p.dot(p) < 1)
            return p;
    }
}

cv::Vec3d random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

cv::Vec3d random_in_unit_disk()
{
    while (true) 
    {
        auto p = cv::Vec3d(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.dot(p) < 1)
        {
            return p;
        }
    }
}

cv::Vec3d random_on_hemisphere(const cv::Vec3d& normal)
{
    cv::Vec3d on_unit_sphere = random_unit_vector();
    if (on_unit_sphere.dot(normal) > 0.0) // in the same hemisphere as the normal
    {
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }
}

cv::Vec3d random_vector()
{
    return cv::Vec3d(random_double(), random_double(), random_double());
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
        return (-half_b - sqrt(discreminant)) / a;
    }
}
