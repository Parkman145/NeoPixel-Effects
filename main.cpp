#include <opencv2/opencv.hpp>
#include <iostream>
#include "CNDA/ndarray.h"
#include "CNDA/array_utilities.h"

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

    auto arr = CNDA::read_np<uint8_t>("sample.npy");

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);

    // auto data = arr.get_data();

    // cv::Mat image(28, 28, CV_8UC1, data.data());
    auto image = Ndarray_to_Mat<uint8_t>(arr);
    cv::imshow("Display window", image);
    cv::waitKey(0);
    return 0;
}
