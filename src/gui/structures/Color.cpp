#include "Color.h"

namespace AGui {


    NormalizedColor::NormalizedColor(float r, float g, float b, float a)
        : r_{r}, g_{g}, b_{b}, a_{a}
    {
    }


    Color::Color(int r, int g, int b, int a)
        : r_{r}, g_{g}, b_{b}, a_{a} {
    }

    NormalizedColor Color::normalize() const {
        float r = (float)((int)((float)r_ / 255.0 * 1000)) / 1000;
        float g = (float)((int)((float)g_ / 255.0 * 1000)) / 1000;
        float b = (float)((int)((float)b_ / 255.0 * 1000)) / 1000;
        float a = (float)((int)((float)a_ / 255.0 * 1000)) / 1000;
        return {r, g, b, a};
    }

} // AGui