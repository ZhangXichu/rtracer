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

    scattered = Ray(record.p, reflected + _fuzziness * random_unit_vector());
    attenuation = _albedo;

    // refected ray should be on the same side of the surface as the normal vector
    return (scattered.direction().dot(record.normal) > 0); 
}

Dialectric::Dialectric(double index_of_refraction)
    :_index_of_refraction(index_of_refraction)
{}

bool Dialectric::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);

    double refraction_ratio = record.front_face ? (1.0 / _index_of_refraction) : _index_of_refraction;

    cv::Vec3d unit_direction = unit_vector(r_in.direction());

    double cos_theta = fmin((-unit_direction).dot(record.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    cv::Vec3d direction;

    if (cannot_refract)
    {
        direction = reflect(unit_direction, record.normal);
    } else 
    {
        direction = refract(unit_direction, record.normal, refraction_ratio);
    }

    scattered = Ray(record.p, direction);

    // cv::Vec3d refracted = refract(unit_direction, record.normal, refraction_ratio);

    // scattered = Ray(record.p, refracted);

    return true;
}
