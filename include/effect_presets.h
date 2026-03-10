#ifndef EFFECT_PRESETS_H
#define EFFECT_PRESETS_H
#include "effects.h"

namespace NEOFX {
namespace effect_presets{

    auto rainbow_pinwheel = NEOFX::pinwheel(NEOFX::rainbow, 1, 1, 0);

    auto white_chase = NEOFX::chase(NEOFX::ColorRamp({NEOFX::black, NEOFX::white, NEOFX::black}, {0.0, 0.025, 0.5}), -0.5, 1.0, 1, 0.1);

    auto rainbow_chaser = [](double x, double y, double t) -> NEOFX::RGB { return rainbow_pinwheel(x, y, t) * white_chase(x, y, t); };


}
}

#endif