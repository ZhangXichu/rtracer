#include <iostream>

#include <utils.hpp>
#include <camera.hpp>

void Camera::render(const Hittable& world)
{
    initialize();

    cv::Mat img(_img_height, img_width, CV_8UC3);

    for (int j = 0; j < _img_height; j++) {
        for (int i = 0; i < img_width; i++) {
            auto pixel_center = _pixel00_loc + (i * _pixel_delta_u) + (j * _pixel_delta_v);
            auto ray_direction = pixel_center - _camera_center;
            Ray ray(_camera_center, ray_direction);

            // Color pixel_color = ray_color(ray);
            Color pixel_color = ray_color(ray, world);

            int ir = static_cast<int>(255.99 * pixel_color[0]);
            int ig = static_cast<int>(255.99 * pixel_color[1]);
            int ib = static_cast<int>(255.99 * pixel_color[2]);

            img.at<cv::Vec3b>(j, i) = cv::Vec3b(ib, ig, ir);
        }
    }

    cv::imwrite("/workspace/output/world.png", img);
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

Color Camera::ray_color(const Ray& ray, const Hittable& world) const
{
    HitRecord record;
    if (world.hit(ray, Interval(0, R_INFINITY), record)) {
        return 0.5 * (record.normal + Color(1, 1, 1));
    }
    cv::Vec3d unit_direction = unit_vector(ray.direction());
    auto a = 0.5 * (unit_direction[1] + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}