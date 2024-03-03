#ifndef HITTABLE_H
#define HITTABLE_H

#include <opencv2/core/matx.hpp>
#include <datatypes.hpp>
#include <ray.hpp>

struct HitRecord {
    Point3 p;
    cv::Vec3d normal;
    double t;
    bool front_face;

    void set_face_normal(const Ray& r, const cv::Vec3d& outward_normal);
};


class Hittable {

public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, double ray_tmain, double ray_tmax, HitRecord& record) const = 0;
};

#endif
