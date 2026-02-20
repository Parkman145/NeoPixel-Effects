#include <opencv2/opencv.hpp>
#include <iostream>
#include "CNDA/ndarray.h"
#include "CNDA/array_utilities.h"
#include "color.h"

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
    double hue = 0;
    double hue_speed = 0.01;
    RGB color = RGB::from_HSV(hue, 1, 1);
    auto image = cv::Mat(400, 400, CV_64FC3, cv::Scalar(color.B, color.G, color.R));
    cv::namedWindow("Display window", cv::WINDOW_NORMAL);
    
    while (true){
        
        hue = fmod(hue+hue_speed, 1.0);
        color = RGB::from_HSV(hue, 1, 1)/2.0;
        image.setTo(cv::Scalar(color.B, color.G, color.R));
        cv::imshow("Display window", image);

        if (cv::waitKeyEx(30) == 27) break;
    }
    cv::destroyAllWindows();
    return 0;
}
