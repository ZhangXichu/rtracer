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
    Metal(const Color& albedo, double fuzziness)
        :_albedo(albedo), _fuzziness(fuzziness < 1 ? fuzziness : 1) {};
    bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

private:
    Color _albedo;
    double _fuzziness;

};

class Dialectric : public Material {
public:
    Dialectric(double index_of_refraction);

    bool scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

private:
    double _index_of_refraction;

    // use Schlick's approximation for reflectivity
    // since the reflectivity changes with angle
    static double reflectance(double cosine, double ref_idx);
};

#endif