#include <sphere.hpp>

Sphere::Sphere(Point3 center, double radius)
    : _center(center), _radius(radius) {}

bool Sphere::hit(const Ray& ray, Interval r_interval, HitRecord& record) const 
{
    cv::Vec3d v_oc = ray.origin() - _center;
    auto a = ray.direction().dot(ray.direction());
    double half_b = v_oc.dot(ray.direction());
    double c = v_oc.dot(v_oc) - _radius * _radius;

    double discreminant = half_b * half_b - a*c;
    if (discreminant < 0) {
        return false;
    }
    auto sqrt_d = sqrt(discreminant);

    // find the nearest root that lies on the acceptable range
    auto root = (-half_b - sqrt_d) / a;
    if (!r_interval.surrounds(root)) {
        root = (-half_b + sqrt_d) / a;
        if (!r_interval.surrounds(root)){
            return false;
        }
    }

    record.t = root;
    record.p = ray.at(record.t);

    cv::Vec3d outward_normal = (record.p - _center) / _radius;

    record.set_face_normal(ray, outward_normal);

    return true;

}