#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <hittable.hpp>

#include <memory>
#include <vector>

class HittableList : public Hittable {

public:
    std::vector<std::shared_ptr<Hittable>> objs;

    HittableList() {}
    HittableList(std::shared_ptr<Hittable> obj) { add(obj); }

    void clear() {
        objs.clear();
    }

    void add(std::shared_ptr<Hittable> obj) {
        objs.push_back(obj);
    }

    bool hit(const Ray& ray, Interval r_interval, HitRecord& record) const override;

};

#endif