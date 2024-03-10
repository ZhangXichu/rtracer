#include <material.hpp>
#include <utils.hpp>

bool Lambertian::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = record.normal + random_unit_vector();

    // catch degenerated scatter direction
    if (near_zero(scatter_direction))
    {
        scatter_direction = record.normal;
    }

    scattered = Ray(record.p, scatter_direction);
    attenuation = _albedo;
    return true;

}

bool Metal::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    cv::Vec3d reflected = reflect(unit_vector(r_in.direction()), record.normal);

    scattered = Ray(record.p, reflected);
    attenuation = _albedo;

    return true;
}