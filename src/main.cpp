#include <opencv2/opencv.hpp>
#include <iostream>
#include "CNDA/ndarray.h"
#include "CNDA/array_utilities.h"
#include "color.h"
#include "effects.h"
#include <string>

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


int main() {
    
    
    
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);
    double loc = 0;
    double speed = 0.01;
    NEOFX::RGB color = NEOFX::RGB::from_HSV(0, 1, 1);
    auto image = cv::Mat(400, 400, CV_64FC3, cv::Scalar(color.B, color.G, color.R));
    cv::namedWindow("Display window", cv::WINDOW_NORMAL);
    
    while (true){
        
        loc = fmod(loc+speed, 1.0);
        NEOFX::ColorRamp color_ramp({NEOFX::red, NEOFX::green, NEOFX::blue}, {0.0, 0.5, 1.0});
        color = color_ramp[loc] / 2;
        image.setTo(cv::Scalar(color.B, color.G, color.R));
        cv::putText(image,  std::to_string(loc), {0, 200}, 1, 2, cv::Scalar(1.0, 1.0, 1.0));
        cv::imshow("Display window", image);
        std::cout << color << "\r";

        if (cv::waitKeyEx(30) == 27) break;
    }
    cv::destroyAllWindows();
    return 0;
}
