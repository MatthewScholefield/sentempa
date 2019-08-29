#pragma once

#include <vector>

#include "Vec.hpp"
#include "types.hpp"

class Renderer;

class Camera;

class StarField {
public:
    void refill(const Camera &camera);
    void update(cfloat dt, const Camera &camera);
    void render(Renderer &renderer, const Camera &camera) const;

private:
    static constexpr int maxStars = 20000;
    static constexpr float starSize = 800.f;

    class Star {
    public:
        void update(cfloat dt);
        Vec3f p;
    };

    std::vector<Star> stars;

    class Box {
    public:
        Vec3f pos;
        Vec3f size;
    };

    // Area containing all existing stars
    Box box;
};
