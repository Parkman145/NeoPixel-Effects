#include <opencv2/opencv.hpp>
#include <iostream>
#include "CNDA/ndarray.h"
#include "CNDA/array_utilities.h"
#include "color.h"
#include "effects.h"
#include <string>
#include <chrono>

template <typename T>
cv::Mat Ndarray_to_Mat(const CNDA::Ndarray<T>& arr) {
    auto shape = arr.get_shape();
    if (shape.size() != 2 && shape.size() != 3) {
        throw CNDA::Ndarray<T>::InvalidShapeException();
    }

    int channels = shape.size() == 2 ? 1 : shape[2];

    int type = CV_MAKETYPE(cv::DataType<T>::type, channels);
    return cv::Mat(shape[0], shape[1], type, const_cast<T*>(arr.get_data().data()));

}

cv::Mat generate_image(std::function<NEOFX::RGB(double, double, double)> func, size_t res_width, size_t res_height, double scale, double t) {
    
    int type = CV_MAKETYPE(cv::DataType<double>::type, 3);

    cv::Mat output(res_width, res_height, type);  

    double scale_x = scale * res_width;
    double scale_y = scale * res_height;

    for (size_t i = 0; i < res_width; i++) {
        double x = (static_cast<double>(i)-(res_width/2)) / scale_x ;
        for (size_t j = 0; j < res_height; j++) {
        double y = (static_cast<double>(j)-(res_height/2)) / scale_y;
            NEOFX::RGB color = func(x, y, t);
            
            output.at<cv::Vec3d>(j, i) = cv::Vec3d(color.B, color.G, color.R);

        }
    }

    return output;


}


int main() {
    size_t res_width = 200;
    size_t res_height = 200;
    double scale = 1;
    double t = 1.0;
    double speed = 0.005;
    std::chrono::steady_clock clock;

    // auto ramp = NEOFX::ColorRamp({ NEOFX::black, NEOFX::blue, NEOFX::black, NEOFX::blue, NEOFX::black, NEOFX::blue, NEOFX::black, NEOFX::blue, NEOFX::black }, { 0.000, 0.125, 0.250, 0.375, 0.500, 0.625, 0.750, 0.875, 1.000 });
    NEOFX::ColorRamp ramp({NEOFX::black, NEOFX::red, NEOFX::black}, {0.0, 0.5, 1.0});
    auto func = NEOFX::pinwheel(ramp, 1, 1, 0, 0, 0.1);



    while (true){
        t -= speed;
        auto im = generate_image(func, res_width, res_height, scale, t);
        cv::imshow("Display window", im);

        if (cv::waitKeyEx(30) == 27) break;
    }
    cv::destroyAllWindows();


    // for (int i = 0; i < result.size(); i++ ) {
    //     std::cout << result[i] << " ";
    // }
    // std::cout << "\n";
    return 0;
}
