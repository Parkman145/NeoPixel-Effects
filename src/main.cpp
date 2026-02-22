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
    
    std::vector<double> x{0.0, 0.0, 1.0, 1.0};
    std::vector<double> y{0.0, 1.0, 0.0, 1.0};
    double t = 1.0;
    std::function func = [](double x, double y, double t) { return NEOFX::radial(x, y, t, NEOFX::rainbow, 1.0, 1.0); };
    auto result = NEOFX::batch_process_array(func, x, y, t);



    for (int i = 0; i < result.size(); i++ ) {
        std::cout << result[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
