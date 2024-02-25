#ifndef RAY_H
#define RAY_H

#include <opencv2/core/matx.hpp>

class Ray
{
public:
    Ray() {}
    Ray(const cv::Vec3d a, const cv::Vec3d& b)
    {
        A = a;
        B = b;
    }
    
    cv::Vec3d origin() const { return A; }
    cv::Vec3d direction() const { return B; }
    cv::Vec3d at(double t) const {
         return A + t*B; 
    }

    cv::Vec3d A;
    cv::Vec3d B;
};

#endif