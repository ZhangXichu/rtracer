#ifndef MATERIAL_H
#define MATERIAL_H

#include <hittable.hpp>

class Hittable;

class Material {

public:
virtual ~Material() = default;

virtual bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;

};

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo)
        : _albedo(albedo) {};
    bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

private:
    Color _albedo;

};

class Metal : public Material {
public:
    Metal(const Color& albedo)
        :_albedo(albedo) {};
    bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

private:
    Color _albedo;

};

#endif