#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/matx.hpp>

#include "ray.hpp"
#include "utils.hpp"

int main()
{
    int num_cols = 400;
    int num_rows = 300;

    // std::cout << "P3\n" << num_cols << " " << num_rows << "\n255\n";

    cv::Mat img(num_rows, num_cols, CV_8UC3);

    cv::Vec3d lower_left(3, 0, 0);
    cv::Vec3d horizontal(1.5, 6, 0);
    cv::Vec3d vertical(-1.5, 2, 0);
    cv::Vec3d center(1.5, 2, 0);

    for (int i = 0; i < num_rows; i++ ) {
        for (int j = 0; j < num_cols; j++) {
            // cv::Vec3d v(i/num_rows, j/num_rows, 0.2);
            double u = double(i) / num_rows;
            double v = double(j) / num_cols;

            Ray ray(center, lower_left + u*horizontal + v*vertical);

            cv::Vec3d col = color(ray);

            // convert color values from double (0.0 to 1.0) to int (0 to 255)
            int ir = static_cast<int>(255.99 * col[0]);
            int ig = static_cast<int>(255.99 * col[1]);
            int ib = static_cast<int>(255.99 * col[2]);

            img.at<cv::Vec3b>(i, j) = cv::Vec3b(ib, ig, ir);
        }
    }

    cv::imwrite("/workspace/output/blue_grad.png", img);

    return 0;
}