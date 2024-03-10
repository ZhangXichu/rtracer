#ifndef SPHERE_H
#define SPHERE_H

#include <hittable.hpp>

class Sphere : public Hittable {
public:
    Sphere(Point3 center, double radius, std::shared_ptr<Material> material);
    bool hit(const Ray& ray, Interval r_interval, HitRecord& record) const override;

private:
    Point3 _center;
    double _radius;
    std::shared_ptr<Material> _material;
};

#endif