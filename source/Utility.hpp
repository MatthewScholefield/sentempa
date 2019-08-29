#pragma once

#include <cmath>
#include "types.hpp"

constexpr float epsilon = 0.00001f;
constexpr float pi = 3.14159265358979f;

constexpr float toRad(cfloat angle) noexcept {
    return angle * pi / 180.f;
}

constexpr float toDeg(cfloat angle) noexcept {
    return angle * 180.f / pi;
}

namespace Utility {
void sleep(unsigned int ms);
}
