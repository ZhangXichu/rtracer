#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/matx.hpp>
#include "opencv2/core/core.hpp"

#include "ray.hpp"
#include "utils.hpp"

int main()
{
    double aspect_ratio = 4.0 / 3.0;
    int img_width = 800;

    // calculate the image height
    int img_height = static_cast<int>(img_width / aspect_ratio);

    cv::Mat img(img_height, img_width, CV_8UC3);
    
    double focal_length = 1.0;
    double view_pt_height = 2.0;
    double view_pt_width = view_pt_height * (static_cast<double>(img_width) / img_height);

    std::cout << "view_pt_width: " << view_pt_width << std::endl; 

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto view_pt_u = cv::Vec3d(view_pt_width, 0, 0);
    auto view_pt_v = cv::Vec3d(0, -view_pt_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = view_pt_u / img_width;
    auto pixel_delta_v = view_pt_v / img_height;

    // Calculate the location of the upper left pixel.
    cv::Vec3d camera_center(0, 0, 0);
    auto view_pt_upper_left = camera_center - cv::Vec3d(0, 0, focal_length) - view_pt_u/2 - view_pt_v/2;

    auto pixel00_loc = view_pt_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    for (int j = 0; j < img_height; j++) {
        for (int i = 0; i < img_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray ray(camera_center, ray_direction);

            Color pixel_color = ray_color(ray);

            int ir = static_cast<int>(255.99 * pixel_color[0]);
            int ig = static_cast<int>(255.99 * pixel_color[1]);
            int ib = static_cast<int>(255.99 * pixel_color[2]);

            img.at<cv::Vec3b>(j, i) = cv::Vec3b(ib, ig, ir);
        }
    }

    cv::imwrite("/workspace/output/norm.png", img);

    return 0;
}