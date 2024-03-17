#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/core.hpp>

#include <hittable.hpp>

class Camera {

public:
    double aspect_ratio = 4.0 / 3.0;
    int img_width = 800;
    int sample_per_pixel = 10;
    int max_depth = 50;

    double vfov = 90; // vertial view angle (field of view)
    cv::Vec3d lookfrom = cv::Vec3d(0, 0, -1); // point camera is looking from
    cv::Vec3d lookat = cv::Vec3d(0, 0, 0); // point camera is looking at
    cv::Vec3d vup = cv::Vec3d(0, 1, 0); // camera relative "up" direction

    void render(const Hittable& world);

private:
    int _img_height;
    Point3 _camera_center;
    Point3 _pixel00_loc;
    cv::Vec3d _pixel_delta_u;
    cv::Vec3d _pixel_delta_v;
    cv::Vec3d u, v, w; // camera frame bassis vectors

    void initialize();

    Color ray_color(const Ray& ray, int depth, const Hittable& world) const;
    Ray get_ray(int i, int j) const;
    cv::Vec3d pixel_sample_square() const;

};

#endif