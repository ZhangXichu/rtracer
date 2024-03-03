#include <iostream>

#include <ray.hpp>
#include <utils.hpp>
#include <hittable.hpp>
#include <sphere.hpp>
#include <camera.hpp>

int main()
{
    // World
    HittableList world;

    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.img_width = 800;
    
    camera.render(world);

    return 0;
}