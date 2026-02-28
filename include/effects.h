#ifndef EFFECTS_H
#define EFFECTS_H
#include <vector>
#include "color.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <functional>

namespace NEOFX {
constexpr double pi = 3.14159265359;

RGB red{1.0, 0.0, 0.0};
RGB orange{1.0, 0.647, 0.0};
RGB yellow{1.0, 1.0, 0.0};
RGB green{0.0, 1.0, 0.0};
RGB blue{0.0, 0.0, 1.0};
RGB purple{0.502, 0.0, 0.502};
RGB white{1.0, 1.0, 1.0};
RGB black{0.0, 0.0, 0.0};

    // A color ramp very similar to the Color Ramp node in blender
class ColorRamp {
    public:
    // Arguments must be passed in ascending order
    ColorRamp() : colors{NEOFX::black}, locations{0.0}{};
    ColorRamp(std::vector<RGB> colors, std::vector<double> locations) : colors{colors}, locations{locations} {
        if (colors.size() != locations.size()) {
            throw std::invalid_argument("Size of colors and locations must match");
        }
    };

    // Interpolate a color at a location. Locations 
    // above and below the ramps bounds will be constrained to 
    // to the highest and lowest values
    RGB operator[](double location) const {
        location = std::max(*locations.begin(), std::min(*(locations.end()-1), location));
        
        // Finding index of location just above the input location
        auto upper_it = std::lower_bound(locations.begin(), locations.end(), location);
        if (upper_it == locations.end()) { upper_it -= 1; }
        size_t upper_index = std::distance(locations.begin(), upper_it);

        // If input location happens to be exactly on a node, simply return it
        // Also naturally handles the case of a node not existing below the input location,
        // since the inpput is clamped. 
        if (location == locations[upper_index]) { return colors[upper_index]; }

        // Interpolate between upper and lower color
        size_t lower_index = upper_index - 1;
        RGB upper_color = colors[upper_index];
        RGB lower_color = colors[lower_index];
        double upper_location = locations[upper_index];
        double lower_location = locations[lower_index];

        double total_dist = upper_location - lower_location;
        double lower_proportion = (upper_location-location)/total_dist;
        double upper_proportion = (location - lower_location)/total_dist;
        RGB result = lower_color*lower_proportion + upper_color * upper_proportion;

        return result;
    }


    private:
    std::vector<RGB> colors;
    std::vector<double> locations;
};

ColorRamp rainbow{{red, orange, yellow, green, blue, purple, red}, {0.0, 0.16666667, 0.33333333, 0.5, 0.66666667, 0.83333333, 1.0}};

struct solid {
    RGB color;
    RGB operator()(double x, double y, double t){ return color; };
};

struct cycle {
    ColorRamp ramp;
    double speed;
    RGB operator()(double x, double y, double t) {
        return ramp[std::fmod(t*speed, 1)];
    }

};

struct radial {
    ColorRamp ramp;
    double speed;
    double scale;
    double center_x = 0.0;
    double center_y = 0.0;
    RGB operator()(double x, double y, double t) {
        double x_dist = x-center_x;
        double y_dist = y-center_y;
        double distance = std::hypot(x_dist, y_dist);
        double phase = t*speed;
        double pos = distance*scale;
        double where = fmod(pos+phase, 1);
        if (where < 0) { where += 1; }
        return ramp[where];
    }
};

struct pinwheel {
    ColorRamp ramp;
    double speed;
    double scale;
    double center_x = 0.0;
    double center_y = 0.0;
    double twist = 0.0;
    RGB operator()(double x, double y, double t) {
        double x_dist = x-center_x;
        double y_dist = y-center_y;
        double angle = (std::atan2(x_dist, y_dist)+pi)/(2*pi);
        double distance = std::hypot(x_dist, y_dist);
        double phase = t*speed;
        double pos = angle+phase+twist*distance;
        double where = fmod(pos+phase, 1);
        if (where < 0) { where += 1; }
        return ramp[where];
    }
};

std::vector<RGB> batch_process(
    std::function<RGB(double, double, double)> func, 
    std::vector<double> x, 
    std::vector<double> y, 
    double t){
    if (x.size() != y.size()) {
        throw std::invalid_argument("Size of x and y must match");
    }

    std::vector<RGB> result;
    result.reserve(x.size()); 
    for (int i = 0; i < x.size(); i++) {
        result.push_back(func(x[i], y[i], t));

    }

    return result;

}


std::vector<double> batch_process_array(
    std::function<RGB(double, double, double)> func, 
    std::vector<double> x, 
    std::vector<double> y, 
    double t){
    if (x.size() != y.size()) {
        throw std::invalid_argument("Size of x and y must match");
    }

    std::vector<double> result;
    result.reserve(x.size()*3); 
    for (int i = 0; i < x.size(); i++) {
        RGB color = func(x[i], y[i], t);
        result.push_back(color.R);
        result.push_back(color.G);
        result.push_back(color.B);
    }

    return result;

}

}


#endif