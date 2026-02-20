#ifndef EFFECTS_H
#define EFFECTS_H
#include <vector>
#include "color.h"
#include <stdexcept>
#include <algorithm>

namespace NEOFX {

class ColorRamp {
    public:
    ColorRamp(std::vector<RGB> colors, std::vector<double> locations) : colors{colors}, locations{locations} {
        if (colors.size() != locations.size()) {
            throw std::invalid_argument("Size of colors and locations must match");
        }
    };

    RGB operator[](double location){
        location = std::clamp(location, *locations.begin(), *(locations.end()-1));
        auto upper_it = std::lower_bound(locations.begin(), locations.end(), location);
        if (upper_it == locations.end()) { upper_it -= 1; }
        size_t upper_index = std::distance(locations.begin(), upper_it);

        if (location == locations[upper_index]) { return colors[upper_index]; }

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

RGB red{1.0, 0.0, 0.0};
RGB orange{1.0, 0.647, 0.0};
RGB yellow{1.0, 1.0, 0.0};
RGB green{0.0, 1.0, 0.0};
RGB blue{0.0, 0.0, 1.0};
RGB purple{0.502, 0.0, 0.502};
RGB white{1.0, 1.0, 1.0};
RGB black{0.0, 0.0, 0.0};


}


#endif