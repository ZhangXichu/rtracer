#include <iostream>

#include <utils.hpp>
#include <camera.hpp>
#include <color.hpp>
#include <material.hpp>

void Camera::render(const Hittable& world)
{
    initialize();

    cv::Mat img(_img_height, img_width, CV_8UC3);

    int num_rays = 5;

    for (int j = 0; j < _img_height; j++) {
        for (int i = 0; i < img_width; i++) {
            Color pixel_color(0, 0, 0);
            for (int sample = 0; sample < sample_per_pixel; ++sample) {

                Ray ray = get_ray(i, j);
                pixel_color += ray_color(ray, max_depth, world);
            }

            img.at<cv::Vec3b>(j, i) = write_color(pixel_color, sample_per_pixel);
        }
    }

    cv::imwrite("/workspace/output/world_glass.png", img);
}

void Camera::initialize()
{
    // calculate the image height
    _img_height = static_cast<int>(img_width / aspect_ratio);
    _img_height = (_img_height < 1) ? 1 : _img_height;

    // _camera_center = Point3(0, 0, 0);
    _camera_center = lookfrom;

    // determine viewport dimensions

    // double focal_length = 1.0;
    // double focal_length = cv::norm(lookfrom - lookat);
    auto theta = degrees_to_radians(vfov);
    auto h = tan(theta/2);
    auto view_pt_height = 2 * h * focus_dist;
    double view_pt_width = view_pt_height * (static_cast<double>(img_width) / _img_height);

    std::cout << "view_pt_width: " << view_pt_width << std::endl; 

    // calculate the u, v, w unit basis vectors for the camera coordinate frame
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(vup.cross(w));
    v = w.cross(u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto view_pt_u = view_pt_width * u; // vecor across viewport horizontal edge
    auto view_pt_v = view_pt_height * (-v); // vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    _pixel_delta_u = view_pt_u / img_width;
    _pixel_delta_v = view_pt_v / _img_height;

    // Calculate the location of the upper left pixel.
    // now the focal length is replaced by the focus distance
    auto view_pt_upper_left =  _camera_center - (focus_dist * w) - view_pt_u/2 - view_pt_v/2;

    _pixel00_loc = view_pt_upper_left + 0.5 * (_pixel_delta_u + _pixel_delta_v);

    // calculate the camera defocus disk basis vectors
    auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

Color Camera::ray_color(const Ray& ray, int depth, const Hittable& world) const
{
    HitRecord record;

    if (depth <= 0)
    {
        return Color(0, 0, 0);
    }

    if (world.hit(ray, Interval(0.005, R_INFINITY), record)) { // ignore hits that are very close to the calculated intersection point 

        Ray scattered;
        Color attenuation;
        if (record.material->scatter(ray, record, attenuation, scattered))
        {
            Color scattered_color = ray_color(scattered, depth - 1, world);

            // return ray_color(scattered, depth-1, world);
            return Color(attenuation[0] * scattered_color[0], attenuation[1] * scattered_color[1], attenuation[2] * scattered_color[2]);
        }
        return Color(0, 0, 0);
    }
    cv::Vec3d unit_direction = unit_vector(ray.direction());
    auto a = 0.5 * (unit_direction[1] + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}

Ray Camera::get_ray(int i, int j) const
{
    // get a radomly sampled camera ray for the pixel at location i, j
    // originates from  the camera defocus disk
    auto pixel_center = _pixel00_loc + (i * _pixel_delta_u) + (j * _pixel_delta_v);
    auto pixel_sample = pixel_center + pixel_sample_square();

    // auto ray_origin = _camera_center;
    auto ray_origin = (defocus_angle <= 0) ? _camera_center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

cv::Vec3d Camera::pixel_sample_square() const 
{
    // Returns a random point in the square surrounding a pixel at the origin
    auto px = -0.5 + random_double();
    auto py = -0.5 + random_double();
    return (px * _pixel_delta_u) + (py * _pixel_delta_v);

}

Point3 Camera::defocus_disk_sample() const
{
    // returns a random point in the camera defocus disk
    auto p = random_in_unit_disk();
    return _camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}