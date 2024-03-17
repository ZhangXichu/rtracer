#include <iostream>

#include <ray.hpp>
#include <utils.hpp>
#include <hittable.hpp>
#include <sphere.hpp>
#include <camera.hpp>
#include <material.hpp>

int main()
{
    // World
    HittableList world;

    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<Dialectric>(1.5);
    auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0, -1.0), -0.4, material_left)); // hollow glass effect
    world.add(std::make_shared<Sphere>(Point3(1.0, 0, -1.0), 0.5, material_right));

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.img_width = 800;
    camera.sample_per_pixel = 80;
    camera.max_depth = 50;

    camera.vfov = 20;
    camera.lookfrom = cv::Vec3d(-2, 2, 1);
    camera.lookat = cv::Vec3d(0, 0, -1);
    camera.vup = cv::Vec3d(0, 1, 0);
    
    camera.render(world);

    return 0;
}