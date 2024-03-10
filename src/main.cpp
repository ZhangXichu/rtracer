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
    auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<Metal>(Color(0.5, 0.7, 0.9));

    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -2), 100, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0, 0, -2), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1, 0, -2), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(1, 0, -2), 0.5, material_right));

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.img_width = 800;
    
    camera.render(world);

    return 0;
}