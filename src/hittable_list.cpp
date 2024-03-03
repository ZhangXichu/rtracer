#include <hittable_list.hpp>

bool HittableList::hit(const Ray& ray, double ray_tmin, double ray_tmax, HitRecord& record) const 
{
    HitRecord tmp_record;
    bool hit_anything = false;
    auto closest_so_far = ray_tmax;

    for (const auto& obj : objs) {
        if (obj->hit(ray, ray_tmin, closest_so_far, tmp_record)) {
            hit_anything = true;
            closest_so_far = tmp_record.t;
            record = tmp_record;
        }
    }

    return hit_anything;
}