#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/matx.hpp>

int main()
{
    int num_cols = 400;
    int num_rows = 300;

    std::cout << "P3\n" << num_cols << " " << num_rows << "\n255\n";

    cv::Mat img(num_rows, num_cols, CV_8UC3);

    for (int i = 0; i < num_rows; i++ ) {
        for (int j = 0; j < num_cols; j++) {
            // cv::Vec3d v(i/num_rows, j/num_rows, 0.2);
            double r = double(i) / num_rows;
            double g = double(j) / num_cols;
            double b = 0.2;

            // convert color values from double (0.0 to 1.0) to int (0 to 255)
            int ir = static_cast<int>(255.99 * r);
            int ig = static_cast<int>(255.99 * g);
            int ib = static_cast<int>(255.99 * b);

            img.at<cv::Vec3b>(i, j) = cv::Vec3b(ib, ig, ir);
        }
    }

    cv::imwrite("/workspace/output/output_image.png", img);

    return 0;
}