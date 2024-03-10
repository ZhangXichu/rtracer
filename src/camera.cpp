#include <iostream>

#include <utils.hpp>
#include <camera.hpp>
#include <color.hpp>

void Camera::render(const Hittable& world)
{
    initialize();

    cv::Mat img(_img_height, img_width, CV_8UC3);

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

    cv::imwrite("/workspace/output/world_lambert.png", img);
}

void Camera::initialize()
{
    // calculate the image height
    _img_height = static_cast<int>(img_width / aspect_ratio);
    _img_height = (_img_height < 1) ? 1 : _img_height;

    _camera_center = Point3(0, 0, 0);

    // determine viewport dimensions
    double focal_length = 1.0;
    double view_pt_height = 2.0;
    double view_pt_width = view_pt_height * (static_cast<double>(img_width) / _img_height);

    std::cout << "view_pt_width: " << view_pt_width << std::endl; 

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto view_pt_u = cv::Vec3d(view_pt_width, 0, 0);
    auto view_pt_v = cv::Vec3d(0, -view_pt_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    _pixel_delta_u = view_pt_u / img_width;
    _pixel_delta_v = view_pt_v / _img_height;

    // Calculate the location of the upper left pixel.
    
    auto view_pt_upper_left = _camera_center - cv::Vec3d(0, 0, focal_length) - view_pt_u/2 - view_pt_v/2;

    _pixel00_loc = view_pt_upper_left + 0.5 * (_pixel_delta_u + _pixel_delta_v);
}

Color Camera::ray_color(const Ray& ray, int depth, const Hittable& world) const
{
    HitRecord record;

    if (depth <= 0)
    {
        return Color(0, 0, 0);
    }

    if (world.hit(ray, Interval(0.001, R_INFINITY), record)) { // ignore hits that are very close to the calculated intersection point 
        // cv::Vec3d direction = random_on_hemisphere(record.normal);
        cv::Vec3d direction = record.normal + random_unit_vector();
        return 0.5 * ray_color(Ray(record.p, direction), depth-1, world); // gray : 50% of the color bounce off
    }
    cv::Vec3d unit_direction = unit_vector(ray.direction());
    auto a = 0.5 * (unit_direction[1] + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}

Ray Camera::get_ray(int i, int j) const
{
    // get a radomly sampled camera ray for the pixel at location i, j
    auto pixel_center = _pixel00_loc + (i * _pixel_delta_u) + (j * _pixel_delta_v);
    auto pixel_sample = pixel_center + pixel_sample_square();

    auto ray_origin = _camera_center;
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