#include <hittable_list.hpp>

bool HittableList::hit(const Ray& ray, Interval r_interval, HitRecord& record) const 
{
    HitRecord tmp_record;
    bool hit_anything = false;
    auto closest_so_far = r_interval.max;

    for (const auto& obj : objs) {
        if (obj->hit(ray, Interval(r_interval.min, closest_so_far), tmp_record)) {
            hit_anything = true;
            closest_so_far = tmp_record.t;
            record = tmp_record;
        }
    }

    return hit_anything;
}