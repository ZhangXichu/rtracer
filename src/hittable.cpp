#include <hittable.hpp>

void HitRecord::set_face_normal(const Ray& ray, const cv::Vec3d& outward_normal) {
    // sets the hit record normal vector
    // assume that outward_normal has normal length
    // this approach lets all the normals always point outward from the surface
    // and the side of the surface is determined at geometry time

    front_face = ray.direction().dot(outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}