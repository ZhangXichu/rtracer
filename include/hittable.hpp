#ifndef HITTABLE_H
#define HITTABLE_H

#include <opencv2/core/matx.hpp>
#include <datatypes.hpp>
#include <ray.hpp>
#include <interval.hpp>
#include <hittable.hpp>

class Material;

struct HitRecord {
    Point3 p;
    cv::Vec3d normal;
    std::shared_ptr<Material> material;
    double t;
    bool front_face;

    void set_face_normal(const Ray& r, const cv::Vec3d& outward_normal);
};


class Hittable {

public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, Interval r_interval, HitRecord& record) const = 0;
};

#endif
