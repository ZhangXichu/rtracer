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
    auto material_center = std::make_shared<Dialectric>(1.5);
    auto material_left = std::make_shared<Dialectric>(1.5);
    auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(1, 0, -1), 0.5, material_right));

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.img_width = 800;
    
    camera.render(world);

    return 0;
}