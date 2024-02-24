#ifndef UTILS_H
#define UTILS_H

#include <ray.hpp>
#include <opencv2/core/matx.hpp>

cv::Vec3d color(const Ray& r);
cv::Vec3d unit_vector(const cv::Vec3d v);


#endif